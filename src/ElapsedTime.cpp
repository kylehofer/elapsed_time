/*
 * File: ElapsedTime.cpp
 * Project: elapsed_time
 * Created Date: Wednesday July 2nd 2025
 * Author: Kyle Hofer
 *
 * MIT License
 *
 * Copyright (c) 2025 Kyle Hofer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
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
 *
 * HISTORY:
 */

#include "ElapsedTime.h"

#ifdef PICO
#include "pico/stdlib.h"
#endif

#if defined(ARDUINO) || defined(ESP8266) || defined(ESP32)
#include <Arduino.h>
#endif

uint32_t ElapsedTime::elapsed()
{

#if defined(PICO)
    uint64_t now = time_us_64();
    uint64_t duration;
    if (now < lastElapsedTime)
    {
        duration = (now + (0xFFFFFFFF ^ lastElapsedTime)) / 1000;
    }
    else
    {
        duration = (now - lastElapsedTime) / 1000;
    }

    lastElapsedTime += (duration * 1000);
#elif defined(ARDUINO) || defined(ESP8266) || defined(ESP32)
    uint32_t now = millis();
    uint32_t duration;
    if (now < lastElapsedTime)
    {
        duration = (now + (0xFFFF ^ lastElapsedTime));
    }
    else
    {
        duration = (now - lastElapsedTime);
    }
    lastElapsedTime = now;
#elif defined(__linux__)
    const auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastElapsedTime);
    lastElapsedTime += duration;

#endif

#if defined(__linux__)
    return duration.count();
#else
    return duration;
#endif
}

ElapsedTime::ElapsedTime()
{
    elapsed();
}
