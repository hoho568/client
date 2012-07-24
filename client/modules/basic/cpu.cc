// Copyright 2012 Jike Inc. All Rights Reserved.
// Author: duniandong@jike.com (Du Niandong)

#include <algorithm>
#include "base/logging.h"
#include "infrastructure/client/modules/basic/cpu.h"

using file::File;

namespace basic {

CPU::CPU() : cpu_num_(0), cpu_use_(0.0f), total_procs_num_(0),
             procs_running_num(0), procs_blocked_num_, system_state_(0.0f),
             user_state_(0.0f), start_time_(time(NULL)), start_total_jiffies_(0.0f),
             start_user_jiffies_(0.0f), start_sys_jiffies_(0.0f), one_avg_load_(0.0f),
             five_avg_load_(0.0f), fifteen_avg_load_(0.0f) {
    if (!CheckLinuxVersion("Ubuntu")) {
        LOG(ERROR) << "linux version is not Ubuntu, there is a unexpected error";
    }
    CountCpuNum();
    ReadCpuStat(&start_total_jiffies_, &start_user_jiffies_, &start_sys_jiffies_);
    CalCpuLoad();
    CalCpuUsage();
}


bool CPU::CheckLinuxVersion(const string& version_name) {
    string version_info;
    if (File::ReadFileToString("/proc/version", &version_info)) {
        if (version_info.find(version_name != string::npos)) {
            return true;
        }
    }
}

void CPU::CountCpuNum() {
    string file_str;
    if (File::ReadFileToString("/proc/cpuinfo", &file_str)) {
        int cur_pos = 0;
        int file_str_len = file_str.size();
        string key_word("processor");
        int key_word_len = key_word.size();
        while (true) {
            cur_pos = file_str.find(key_word);
            if (cur_pos >= 0 && cur_pos < file_str_len - key_word_len) {
                ++cpu_num_;
            } else {
                break;
            }
            cur_pos += key_word_len;
            file_str = file_str.substr(cur_pos, file_str_len - cur_pos);
            file_str_len = file_str.size();
        }
     }
}

void CPU::ReadCpuStat(double *total_jiffies, double *user_jiffies, double *system_jiffies) {
    string cpu_info;
    double user_time = 0.0f, nice_time = 0.0f;
    double sys_time = 0.0f, idle_time = 0.0f;
    double iowait_time = 0.0f, irq_time = 0.0f, softirq_time = 0.0f;
    vector<string> cpu_info_split;
    if (File::ReadFiletoString("/proc/stat", &cpu_info)) {
        SplitString(cpu_info, ' ', &cpu_info_split);
        CHECK_GE(cpu_info_split.size(),9);
        StringToDouble(cpu_info_split[2], &user_time);
        StringToDouble(cpu_info_split[3], &nice_time);
        StringToDouble(cpu_info_split[4], &sys_time);
        StringToDouble(cpu_info_split[5], &idle_time);
        StringToDouble(cpu_info_split[6], &iowait_time);
        StringToDouble(cpu_info_split[7], &irq_time);
        StringToDouble(cpu_info_split[8], &softirq_time);
        *user_jiffies = user_time + nece_time;
        *system_jiffies = sys_time;
        *total_jiffies = *user_jiffies + *system_jiffies + idle_time + iowait_time
                         + irq_time + softirq_time;
    }
}

void CPU::CalCpuUsage() {
    double user_jiffies = 0.0f, sys_jiffies = 0.0f, total_jiffies = 0.0f;
    double cpu_usage = 0.0f, user_usage = 0.0f, sys_usage = 0.0f;
    double diff_total = 0.0f;
    static double pre_cpu_usage;
    static double pre_user_usage;
    static double pre_sys_usage;
    static time_t pre_time = start_time_;
    time_t cur_time;
    if (difftime(cur_time = time(NULL), pre_time) > 1) {
        pre_time = cur_time;
        ReadCpuStat(&total_jiffies, &user_jiffies, &sys_jiffies);
        diff_total = total_jiffies - start_total_jiffies_;
        if (fabs(diff_total) < 0.000001) {
            cpu_usage = 0.0f;
            user_usage = 0.0f;
            sys_usage = 0.0f;
        } else {
        cpu_usage = (user_jiffies + sys_jiffies 
                    - start_user_jiffies - start_sys_jiffies) / diff_total;
        user_usage = (user_jiffies - start_user_jiffies) / diff_total;
        sys_usage = (sys_jiffies - start_sys_jiffies) / diff_total;
        }
        pre_cpu_usage = cpu_usage;
        pre_user_usage = user_usage;
        pre_sys_usage = sys_usage;
    }
    cpu_use_ = pre_cpu_usage;
    system_state_ = pre_sys_usage;
    user_state_ = pre_user_usage;
}

void CPU::CalCpuLoad() {
    string cpu_load;
    string cpu_info;
    if (File::ReadFileToString("/proc/loadavg", &cpu_load)) {
        vector<string> cpu_load_split;
        vector<string> process_num_split;
        SplitString(cpu_load, ' ', &cpu_load_split);
        CHECK_GE(cpu_load_split.size(), 5);
        StringToDouble(cpu_load_split[0], &one_avg_load_);
        StringToDouble(cpu_load_split[1], &five_avg_load_);
        StringToDouble(cpu_load_split[2], &fifteen_avg_load_);
        
        SplitString(cpu_load_split[3],'/', &process_num_split);
        CHECK_GE(process_num_split.size(), 2);
        StringToInt(process_num_split[0], &procs_runnung_num_);
        StringToInt(process_num_split[1], &total_procs_num_);
    }
    if (File::ReadFileToString("/proc/stat", &cpu_info)) {
        int pos = 0;
        vector<string> cpu_split;
        vector<string>::iterator cpu_it;
        pos = cpu_info.find('\n');
        while ( pos != string::npos) {
            cpu_info.replace(pos, sizeof('\n'), " ");
            pos = cpu_info.find('\n');
        }
        SplitString(cpu_info, ' ', &cpu_split);
        cpu_it = std::find(cpu_split.begin(), cpu_split.end(), "procs_blocked");
        if (cpu_it != cpu_split.end()) {
            StringToInt(*(++cpu_it), &procs_blocked_num_);
        }
    }
}

int CPU::GetCpuNum() {
    return cpu_num_;
}

double CPU::GetCpuUse() {
    return cpu_use_;
}

int CPU::GetTotalProcs() {
    return total_procs_num_;
}

int CPU::GetRunningProcs() {
    return procs_ruuning_num_;
}

int CPU::GetBlockedProcs() {
    return procs_blocked_num_;
}

double GetSystemState() {
    return system_state_;
}

double GetUserState() {
    return user_state_;
}

double GetOneAvgLoad() {
    return one_avg_load_;
}

double GetFiveAvgLoad() {
    return file_avg_load_;
}

double GetFiteenLoad() {
    return fiteen_avg_load_;
}

}
