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

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleRecurse(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& workedShifts,
    size_t day
);


// Add your implementation of schedule() and other helper functions here

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

    // Create vectors for the days in schedule
    for(size_t i=0; i<avail.size(); i++){
        sched.push_back(vector<Worker_T>());
    }

    // Keep track of user shift number
    vector<size_t> workedShifts(avail[0].size(), 0);

    // Recursive backtrack with day set to 0
    return scheduleRecurse(avail, dailyNeed, maxShifts, sched, workedShifts, 0);

}

// Helper recursive backtrack function
bool scheduleRecurse(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& workedShifts,
    size_t day
){

    // Base case: if the days are all scheduled
    if(day >= avail.size()){
        return true;
    }

    // Loop through workers for the day
    for(Worker_T w = 0; w < avail[0].size(); w++){
        // Check if worker can work for that day
        if(avail[day][w] == 1){
            // Check to see if worker can work that day
            if(workedShifts[w] < maxShifts){
                // Check with find algorithm to make sure the worker has not been scheduled for this day already
                if(find(sched[day].begin(), sched[day].end(), w) == sched[day].end()){
                    // Add worker to work for this day
                    sched[day].push_back(w);
                    workedShifts[w]++;

                    // Move onto the next day if the current day is already full with recursion
                    if(sched[day].size() == dailyNeed){
                        if(scheduleRecurse(avail, dailyNeed, maxShifts, sched, workedShifts, day+1)){
                            return true;
                        }
                    }
                    // Add another worker to this current day with recursion
                    else{
                        if(scheduleRecurse(avail, dailyNeed, maxShifts, sched, workedShifts, day)){
                            return true;
                        }
                    }
                
                    // Backtrack
                    sched[day].pop_back();
                    workedShifts[w]--;
                }
            }
        }
    }

    // Unable to completely schedule this day or schedule anyone at all if not empty here
    return false;
}
