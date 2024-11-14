#ifndef PRINTER_JOB_HEADER
#define PRINTER_JOB_HEADER

#include <string>

class Printer_Job
{
public:
    Printer_Job(const std::string& name, int pages)
        : job_name(name), page_count(pages) {}

    std::string get_name() const;
    int get_page_count() const;

private:
    std::string job_name; // ��� �������
    int page_count;       // ���������� ������� ��� ������
};

void print_job(const Printer_Job& job);

#endif;