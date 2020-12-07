#ifndef ERRCHECK_H
#define ERRCHECK_H

#include <vector>
#include <string>

typedef unsigned long long ull;

//Общая обработка
void errcheck(bool require, const char *success, const char *fail, int errorcode = 0, bool successmsg = true);

//Обработки ошибок для чисел
int getpositivenum(const char *str, const char *errstr = "Некорректный ввод");
int getnum_in_interval(const char *str, const int start, const int stop,
							  const char *errstr = "Некорректный ввод", const short wid = 0);
int getnum_in_arr(const char *str, std::vector<size_t> arr, const char *errstr = "Некорректный ввод", const int wid = 0);
int getindex(const char *str, const int size);

//Обработка строк
bool is_ull(const std::string str);
bool is_f(const std::string str);
int _ull_comprison(std::string left, std::string right);
int _f_comprison(std::string left, std::string right);


#endif // ERRCHECK_H
