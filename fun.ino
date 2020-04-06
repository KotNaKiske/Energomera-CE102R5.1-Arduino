// Переменные, создаваемые процессом сборки,
// когда компилируется скетч
extern int __bss_end;
extern void *__brkval;
// Функция, возвращающая количество свободного ОЗУ (RAM)
int memoryFree()
{
  int freeValue;
  if ((int)__brkval == 0)
    freeValue = ((int)&freeValue) - ((int)&__bss_end);
  else
    freeValue = ((int)&freeValue) - ((int)__brkval);
  return freeValue;
}

int readfile() {
  for (int i = 0; i < file.size(); i++) //Read upto complete file size
  {
    Serial.print((char)file.read());
  }
}
