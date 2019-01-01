#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/syscall.h>
#include <sstream>
#include "ThreadPool.h"

using namespace std;

void printer_1()
{
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    std::string stid = oss.str();
    unsigned long long tid = std::stoull(stid);
    cout << "this is printer 1" << "  thread id: "<< tid << endl;
}

void printer_2()
{
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    std::string stid = oss.str();
    unsigned long long tid = std::stoull(stid);
    cout << "this is printer 2" << "  thread id: " << tid << endl;
}

void printer_3(string s)
{
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    std::string stid = oss.str();
    unsigned long long tid = std::stoull(stid);
    cout << "this is printer 3 with parameter: " << s << "   thread id: " << tid << endl;
}

void printer_4()
{
    std::ostringstream oss;
    oss << std::this_thread::get_id();
    std::string stid = oss.str();
    unsigned long long tid = std::stoull(stid);
    cout << "this is printer 4 " << "thread id: " << tid << endl;
}

void printer_5()
{

    std::ostringstream oss;
    oss << std::this_thread::get_id();
    std::string stid = oss.str();
    unsigned long long tid = std::stoull(stid);
    cout << "this is printer 5 " << "thread id: " << tid << endl;
}

int main() {

    ThreadPool threads(2);
    threads.AddTask(printer_1);
    threads.AddTask(printer_2);
    threads.AddTask(bind(printer_3, "this is string parameter"));
    threads.AddTask(printer_4);
    threads.AddTask(printer_5);
    //sleep(2);

    return 0;
}