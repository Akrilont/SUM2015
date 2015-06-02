#include <stdio.h>
#include <windows.h>
void main( void )
{
  if((MessageBox(NULL, "Ваш выбор?", "Question", MB_YESNO | MB_ICONQUESTION)) == IDNO)
    MessageBox(NULL, "NO", "Ваш Выбор", MB_YESNO | MB_ICONINFORMATION);
  else
    MessageBox(NULL, "YES", "Ваш Выбор", MB_YESNO | MB_ICONINFORMATION);
}