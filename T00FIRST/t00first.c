#include <stdio.h>
#include <windows.h>
void main( void )
{
  if((MessageBox(NULL, "��� �����?", "Question", MB_YESNO | MB_ICONQUESTION)) == IDNO)
    MessageBox(NULL, "NO", "��� �����", MB_YESNO | MB_ICONINFORMATION);
  else
    MessageBox(NULL, "YES", "��� �����", MB_YESNO | MB_ICONINFORMATION);
}