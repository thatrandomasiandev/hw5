#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCounts,
    const size_t idx
);


// Add your implementation of schedule() and other helper functions here

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftCounts,
    const size_t idx
)
{
    const size_t n = avail.size();
    if (idx == n * dailyNeed) {
        return true;
    }

    const size_t day = idx / dailyNeed;
    const size_t posInDay = idx % dailyNeed;
    const size_t k = avail[day].size();

    for (size_t w = 0; w < k; w++) {
        if (!avail[day][w]) {
            continue;
        }
        if (shiftCounts[w] >= maxShifts) {
            continue;
        }
        if (find(sched[day].begin(), sched[day].begin() + posInDay, w)
            != sched[day].begin() + posInDay) {
            continue;
        }

        sched[day][posInDay] = w;
        shiftCounts[w]++;

        if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, idx + 1)) {
            return true;
        }

        shiftCounts[w]--;
    }

    return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    const size_t n = avail.size();
    const size_t k = avail[0].size();

    sched.resize(n);
    for (size_t day = 0; day < n; day++) {
        sched[day].resize(dailyNeed);
    }

    vector<size_t> shiftCounts(k, 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCounts, 0);
}
