void startwww() {
  server.on("/123", []() {
    server.send(200, "text/plain", "Отличная работа!");
  });
  server.on("/", send232);
  server.on("/info", sendinfo);
  server.begin();
  Serial.println("HTTP-сервер запущен");
}

void send232() { // Обработчик запроса клиента по корневому адресу
  String SSSS;
  for (int i = 0; i < SSS.length(); i++)
    SSSS += dobnull(String(SSS[i], HEX)) + "|";
  server.send(200, "text/plain", "Time=" + String(Time) + "\n" +
              "Etope=" + String(Etope) + "\n" +
              "SSS=" + String(SSSS) + "\n");
}

void sendinfo() {
  String S;
  FSInfo fs_info;
  S = S + "Start\n";
  S = S + "ID ESP8266: ";
  S = S + ESP.getChipId();
  S = S + "ID flash memory: ";
  S = S + ESP.getFlashChipId();
  S = S + "Version SDK: ";
  S = S + ESP.getSdkVersion();
  S = S + "\n";
  S = S + "MHz CPU: ";
  S = S + ESP.getCpuFreqMHz();
  S = S + "MHz memory: ";
  S = S + ESP.getFlashChipSpeed() / 1000000;
  S = S + "\n";
  S = S + "Flash memory SDK (Mb): ";
  S = S + ESP.getFlashChipSize() / 1048576;
  S = S + "Flash memory ID chip (Mb): ";
  S = S + ESP.getFlashChipRealSize() / 1048576;
  S = S + "\n";
  S = S + "Free memory: ";
  S = S + ESP.getFreeHeap();
  S = S + "Free memory sketch: ";
  S = S + ESP.getFreeSketchSpace();
  S = S + "Size sketch: ";
  S = S + ESP.getSketchSize();
  S = S + "\n";
  S = S + "\n";
  SPIFFS.info(fs_info);
  S = S + "totalBytes: ";
  S = S + fs_info.totalBytes;
  S = S + "\nusedBytes: ";
  S = S + fs_info.usedBytes;
  S = S + "\nblockSize: ";
  S = S + fs_info.blockSize;
  S = S + "\npageSize: ";
  S = S + fs_info.pageSize;
  S = S + "\nmaxOpenFiles: ";
  S = S + fs_info.maxOpenFiles;
  S = S + "\nmaxPathLength: ";
  S = S + fs_info.maxPathLength;
  S = S + "\n\n";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    S = S + "\n" + dir.fileName() + "\t";
    File f = dir.openFile("r");
    S = S + f.size();
  }
  server.send(200, "text/plain", S);
  delay (10000);
}
