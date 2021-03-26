/**
 * MIT License
 *
 * Copyright (c) 2021 Mathieu Rabine
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// meminfo.
#include "version.h"

// C++.
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <map>

// C.
#include <sys/signalfd.h>
#include <sys/select.h>
#include <fnmatch.h>
#include <unistd.h>
#include <curses.h>
#include <getopt.h>
#include <dirent.h>
#include <signal.h>
#include <cstdio>

/**
 * @brief trim left.
 * @param s string to trim.
 * @return trimed string.
 */
std::string& trimLeft (std::string& s)
{
    return s.erase (0, s.find_first_not_of ("\f\t\v\r\n"));
}

/**
 * @brief trim right.
 * @param s string to trim.
 * @return trimed string.
 */
std::string& trimRight (std::string& s)
{
    return s.erase (s.find_last_not_of (" \f\t\v\r\n") + 1);
}

/**
 * @brief trim.
 * @param s string to trim.
 * @return trimed string.
 */
std::string& trim (std::string& s)
{
    return trimLeft (trimRight (s));
}

/**
 * @brief is number.
 * @param s string to check.
 * @return true if number.
 */
bool isNumber (const std::string& s)
{
    return !s.empty () && std::all_of (s.begin (), s.end (), ::isdigit);
}

/**
 * @brief print binary version.
 */
void version ()
{
    std::cout << BINARY_NAME << " version " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
}

/**
 * @brief print binary usage.
 */
void usage ()
{
    std::cout << "Usage" << std::endl;
    std::cout << "  " << BINARY_NAME << " [options] [name]" << std::endl;
    std::cout << std::endl;
    std::cout << "Options" << std::endl;
    std::cout << "  -d delay          delay between updates (default: 5 seconds)" << std::endl;
    std::cout << "  -h                show available options" << std::endl;
    std::cout << "  -n number         number of iterations" << std::endl;
    std::cout << "  -v                print version" << std::endl;
}

/**
 * @brief main function.
 * @param argc number of command line arguments.
 * @param argv command line arguments. 
 */ 
int main (int argc, char** argv)
{
    std::chrono::milliseconds delay (5000);
    std::string pattern ("*");
    int iterations = 17280;

    for (;;)
    {
        int command = getopt (argc , argv, "d:hn:v");
        if (command == -1)
        {
            break;
        }

        switch (command)
        {
            case 'd':
                delay = std::chrono::milliseconds (std::stoi (optarg) * 1000);
                break;
            case 'h':
                usage ();
                _exit (EXIT_SUCCESS);
            case 'n':
                iterations = std::stoi (optarg);
                break;
            case 'v':
                version ();
                _exit (EXIT_SUCCESS);
            default:
                usage ();
                _exit (EXIT_FAILURE);
        }
    }

    if ((argc - optind) > 2)
    {
        usage ();
        _exit (EXIT_FAILURE);
    }

    if ((argc - optind) == 1)
    {
        pattern = argv[optind];
    }

    sigset_t sigmask;
    sigemptyset (&sigmask);
    sigaddset (&sigmask, SIGINT);
    pthread_sigmask (SIG_BLOCK, &sigmask, nullptr);

    int sig = signalfd (-1, &sigmask, 0);
    if (sig == -1)
    {
        _exit (EXIT_FAILURE);
    }

    fd_set setfd;
    FD_ZERO (&setfd);
    FD_SET (sig, &setfd);
    int max = sig;

    initscr ();

    for (int i = 0; i < iterations; ++i)
    {
        std::string proc ("/proc/");
        std::multimap <std::string, std::string, std::greater <std::string>> memusage;
        struct dirent **entries;

        int num = scandir (proc.c_str (), &entries, nullptr, nullptr);
        if (num >= 0)
        {
            for (int n = 0; n < num ; ++n)
            {
                if (isNumber (entries[n]->d_name))
                {
                    std::ifstream status (proc + entries[n]->d_name + "/status");
                    if (status)
                    {
                        std::string name, rss;
                        for (std::string line; std::getline (status, line);)
                        {
                            if (line.compare (0, 6, "VmRSS:") == 0)
                            {
                                rss = line.substr (line.find (":", 0) + 1);
                                trim (rss);
                            }

                            if (line.compare (0, 5, "Name:") == 0)
                            {
                                name = line.substr (line.find (":", 0) + 1);
                                trim (name);
                            }
                        }

                        if (!rss.empty () && !name.empty () && (fnmatch (pattern.c_str (), name.c_str (), 0) == 0))
                        {
                            memusage.emplace (rss, name);
                        }
                    }
                }
                free (entries[n]);
            }
            free (entries);
        }

        int row = 0, column = 15;

        clear ();
        attron (A_BOLD);
        mvprintw (row, 6, "VmRSS");
        mvprintw (row++, column, "Name");
        attroff (A_BOLD);
        for (auto const& mem: memusage)
        {
            mvprintw (row, 0, "%s", mem.first.c_str ());
            mvprintw (row++, column, "%s", mem.second.c_str ());
        }
        move (0, 0);
        refresh ();

        if ((i < (iterations - 1)) && delay.count ())
        {
            fd_set set = setfd;

            timeval time;
            time.tv_sec = delay.count () / 1000;
            time.tv_usec = (delay.count () % 1000) * 1000;

            int nset = ::select (max + 1, &set, nullptr, nullptr, &time);
            if (nset > 0)
            {
                struct signalfd_siginfo siginfo;
                if(::read (sig, &siginfo, sizeof (struct signalfd_siginfo)) != sizeof (struct signalfd_siginfo))
                {
                    close (sig);
                    _exit (EXIT_FAILURE);
                }

                if(siginfo.ssi_signo == SIGINT)
                {
                    break;
                }
            }
        }
    }

    close (sig);
    endwin ();

    _exit (EXIT_SUCCESS);
}
