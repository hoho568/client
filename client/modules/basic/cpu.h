// Copyright 2012 Jike Inc. All Rights Reserved.
// Author: duniandong@jike.com (Du Niandong)

#include <cmath>
#include <vector>
#include <ctime>
#include <utility>
#include "base/yr.h"
#include "base/flags.h"
#include "base/time.h"

namespace basic {

class CPU {
    public:
        CPU();
        int GetCpuNum();
        double GetCpuUse();
        int GetTotalProcs();
        int GetRunningProcs();
        int GetBlockedProcs();
        double GetSysState();
        double GetUserState();
        double GetOneAvgLoad();
        double GetFiveAvgLoad();
        double GetFittenAvgLoad();
        std::string GetSystemState();
        std::string GetUserState();
        GetAvgLoad();
    private:
        bool CheckLinuxVersion(const std::string &version_name);
        void CountCpuNum();
        void ReadCpuStat(double *total_jiffies, double *user_jiffies, double *sys_jiffies);
        void CalCpuUsage();
        void CalCpuLoad();


    private:
        int cpu_num_;
        double cpu_use_;
        int total_procs_num_;
        int procs_running_num_;
        int procs_blocked_num_;
        double system_state_;
        double user_state_;
        time_t start_time_;
        double start_total_jiffies_;
        double start_user_jiffies_;
        double start_sys_jiffies_;
        double one_avg_load_;
        double five_avg_load_;
        double fifteen_avg_load_;
}
}

