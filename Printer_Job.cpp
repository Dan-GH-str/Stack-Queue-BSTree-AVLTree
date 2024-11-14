#include "Printer_Job.h"

#include <string>
#include <iostream>
#include <thread>
#include <chrono>

std::string Printer_Job::get_name() const { return job_name; }
int Printer_Job::get_page_count() const { return page_count; }

void print_job(const Printer_Job& job) {
    std::cout << "Начало печати задания: " << job.get_name()
        << " (" << job.get_page_count() << " страниц)" << std::endl;

    // Симуляция времени печати
    std::this_thread::sleep_for(std::chrono::seconds(job.get_page_count()));

    std::cout << "Задание \"" << job.get_name() << "\" завершено." << std::endl;
}