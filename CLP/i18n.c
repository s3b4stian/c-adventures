#include <wchar.h>
#include <wctype.h>
#include <locale.h>

int main (void)
{
    //Per the C standard, each FILE stream has associated with it an "orientation" 
    //(either "byte" or "wide) which is set by the first operation performed on it, 
    //and which can be inspected with the fwide function. 
    //Calling any function whose orientation conflicts with the orientation of the 
    //stream results in undefined behavior.
    setlocale (LC_ALL, "");

    //determine the size of the wide char and wide int data types
    wprintf (L"sizeof(wchar_t):%ld sizeof(wint_t):%ld\n", sizeof(wchar_t), sizeof (wint_t));

    wchar_t omega = L'\u03a9';
    wprintf (L"Characters: %lc %lc \n", L'a', 65);
    wprintf (L"Decimals: %d %ld\n", 1977, 650000L);
    wprintf (L"Preceding with blanks: %10d \n", 1977);
    wprintf (L"Preceding with zeros: %010d \n", 1977);
    wprintf (L"Some different radixes: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
    wprintf (L"floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
    wprintf (L"Width trick: %*d \n", 5, 10);
    wprintf (L"%ls \n", L"A wide string");

    wchar_t omega1 = L'\u03a9';
    wprintf (L"%lc\n", omega1);

    wchar_t *str1 = L"υπολογιστή";	// computer
    wchar_t str2[] = L"πρόγραμμα";	// program
    wchar_t str[100];
    wprintf (L"%ld\n", wcslen (str1));
    wprintf (L"%ld\n", wcslen (str2));
    wcscpy (str, str1);
    wcscat (str, L" ");
    wcsncat (str, str2, 5);
    wprintf (L"%ld\n", wcslen (str));


    return 0;
}