void EnergomeraCycle()//начало
{
  if (UART.available())
  {
    char response = UART.read();
    //Serial.print(" " + String(response, HEX) + " ");
    //c0  48  fd  0  69  d5  57  1  20  36  04  20  06  04  04  20  87  c0
    //36  4  20  6  4  4  20 2020-04-04 суббота 20:04:36
    //c0  48  fd  0  69  d5  57  1  30  00  04  20 !35  4a  00  00! bc  c0
    //189.97
    SSS += response;
    if (response == 0xC0) {
      if (ReadStr.length() > 2) {
        if (ReadStr[7] == 0x20) { //время пришло
          Time = "20" + String(ReadStr[14], HEX) + "-" + dobnull(String(ReadStr[13], HEX)) + "-" + dobnull(String(ReadStr[12], HEX)) + " " +
                 dobnull(String(ReadStr[10], HEX))  + ":" + dobnull(String(ReadStr[9], HEX)) + ":" + dobnull(String(ReadStr[8], HEX));
          //Time = int(String(ReadStr[10], HEX)) * int(String(ReadStr[9], HEX));
          Serial.println("Time=" + Time + " ");
          SSS = "";
          //Date = String(ReadStr[14], HEX) + dobnull(String(ReadStr[14], HEX)) + dobnull(String(ReadStr[12], HEX));

          //Time=20450413
        }
        if (ReadStr[7] == 0x60) { // 
          //fc|c0|48|fd|00|69|d5|5c|01|60|00|01|00|0b|04|03|00|01|00|01|00|01|92|c0|
          //fc|c0|48|fd|00|69|d5|5c|01|60|00|01|00|0b|04|03|00|01|00|01|00|01|92|c0|
          Etope = "";
          for (int i = 0; i < ReadStr.length(); i++)
            Etope += dobnull(String(ReadStr[i], HEX)) + "|";
        }
        if (ReadStr[7] == 0x30) { //показания пришли
          Etope = "";
          //for (int i = 0; i < ReadStr.length(); i++)
          //  Etope += dobnull(String(ReadStr[i], HEX)) + "|";
          Etope += long(strtol(String(ReadStr[14], HEX).c_str() , NULL, 16) * 16777216 +
                        strtol(String(ReadStr[13], HEX).c_str() , NULL, 16) * 65535 +
                        strtol(String(ReadStr[12], HEX).c_str() , NULL, 16) * 256 +
                        strtol(String(ReadStr[11], HEX).c_str() , NULL, 16));
          Serial.println("Etope=" + String(ReadStr[14], HEX) + String(ReadStr[13], HEX) + String(ReadStr[12], HEX) + String(ReadStr[11], HEX) + " = " + String(Etope) + " ");

          //190/10
        }
      };
      ReadStr = "";
    } else
      ReadStr += response;
  }
}
String dobnull(String s)
{
  if (s.length() == 0)
    return "00";
  if (s.length() == 1)
    return "0" + s;
  return s;
}
void SendCommand(byte * cmd, int size)
{
  digitalWrite(DIR, HIGH);
  UART.write (cmd, size);
  digitalWrite(DIR, LOW);
}

void EmergomeraWrite(int Step)
{
  switch (Step) {
    case 0:
      SendCommand(CmdTime, 15);
      break;
    case 1:
      //SendCommand(CmdVolt, 15);
      SendCommand(CmdEtope, 17);
      break;
    default:
      break;
  }
}
