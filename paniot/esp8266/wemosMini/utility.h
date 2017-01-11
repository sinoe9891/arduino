//format bytes
String formatBytes(size_t bytes){
  if (bytes < 1024){
    return String(bytes)+"B";
  } else if(bytes < (1024 * 1024)){
    return String(bytes/1024.0)+"KB";
  } else if(bytes < (1024 * 1024 * 1024)){
    return String(bytes/1024.0/1024.0)+"MB";
  } else {
    return String(bytes/1024.0/1024.0/1024.0)+"GB";
  }
}

String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

String addESPInfo() {
  String jsonData = "";
  jsonData += "{\"freeHeap\": \""+String(ESP.getFreeHeap())+"\"";
  jsonData += ",\"resetReason\": \""+String(ESP.getResetReason())+"\"";
  jsonData += ",\"deviceName\": \""+deviceName+"\"";
  jsonData += ",\"deviceLocation\": \""+deviceLocation+"\"";
  jsonData += ",\"rssi\":\""+String(WiFi.RSSI())+"\"";
  jsonData += ",\"ip\":\""+String(WiFi.localIP())+"\"";
  jsonData += "}";
  return jsonData;
}
