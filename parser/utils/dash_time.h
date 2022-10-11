// Copyright 2012 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma  once

#include <optional>
#include <string>

namespace dash {

/**
 * ParseTimeString wrap the PR_ParseTimeString.
 * @return uint64_t if success. Return epoch time in microsecond since midnight (00:00:00),
* January 1, 1970 Greenwich Mean Time(UTC)
 * */
std::optional<int64_t> ParseTimeString(const std::string& s);

/**
 * @brief ParseDurationString only support convert the ISO8601 duration into a struct.
 * For example: PT568.500S , P3DT15H6M3.000S , PT 5000.000S
 * It only support the decimal number in second.
 * Note that the month and year in duration should not be manipulated.
 * For example, what does "a month from January 31st" mean?
 * That is mean, the maximum scale is day.
 * @return int64_t, if parsed successfully, it will return the duration in microsecond.
 * */
std::optional<int64_t> ParseDurationString(const std::string& duration);

/**
 * @brief DateAdvance will add the @param duration to the @param date in order to
 * @param date the current date
 * @param delta the duration of advancing
 * @return the epoch time in microsecond since midnight (00:00:00),
* January 1, 1970 Greenwich Mean Time(UTC)
 * */
std::optional<int64_t> DateAdvance(std::string& date, std::string& delta);

/**
 * @brief DateRewind will rewind the date by delta duration.
 * @param date the original date
 * @param delta the duration of rewinding
 * @return the epoch time in microsecond since midnight (00:00:00),
 * January 1, 1970 Greenwich Mean Time(UTC)
 * */
std::optional<int64_t> DateRewind(std::string& date, std::string& delta);


}  // namespace dash