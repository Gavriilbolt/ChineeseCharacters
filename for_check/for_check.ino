// Библиотекки для работы с SD картой по SPI
  #include <SPI.h>
  #include <SD.h>

// Библиотеки для работы с аналоговой клавиатурой
  #include <EncButton.h>
  #include <AnalogKey.h>

// Библиотека для работы с OLED дисплеем
  #include "U8glib.h"


// константы
  #define KB_PIN 0
  const int chipSelect = 4; // Пин выбора для SD модуля
  


// объявление кнопок
  EncButton<EB_TICK, VIRT_BTN> btn1;
  EncButton<EB_TICK, VIRT_BTN> btn2;
  EncButton<EB_TICK, VIRT_BTN> btn3;
  EncButton<EB_TICK, VIRT_BTN> btn4;
  EncButton<EB_TICK, VIRT_BTN> btn5;
  EncButton<EB_TICK, VIRT_BTN> btn6;

// создаём массив значений сигналов с кнопок
  int16_t sigs[6] = {
    267, 143, 539,
    393,  1024,  732
  };

// указываем пин, количество кнопок и массив значений
  AnalogKey<KB_PIN, 6, sigs> keys;


// Инициализация дисплея
  U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TW

// создание объекта для работы с файлом
  File dataFile;

void WriteToFile(const String& inf){
  // Открываем файл для записи
  dataFile = SD.open("data.txt", FILE_WRITE);
  
  if (dataFile) {
    // Записываем строку в файл
    dataFile.println(inf);
    
    dataFile.close(); // Закрываем файл
  } else {
    Serial.println("Ошибка открытия файла.");
  }

}


// Отрисовка на дисплей
void drawBTNState(const char* state) {
  u8g.setFont(u8g_font_unifont);  // Шрифт для текста меню
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();

  // Дублирование состояние кнопок в COM порт
  Serial.println(state);
  WriteToFile(state);
  u8g.firstPage();
  do {
    // Вывод значения на дисплей
    u8g.drawStr(0, 0, state);


  } while (u8g.nextPage());
}


void setup() {
  // инициализация общения с МК по Serial (COM порт -> монитор порта)
  Serial.begin(9600);
  drawBTNState(""); // Вызов функции, для избежания артифактов на дисплее

  // обработка SD карты
    // Инициализация SD карты
  if (!SD.begin(chipSelect)) {
    Serial.println("Ошибка инициализации SD карты.");
    return;
  }
  
  Serial.println("SD карта инициализирована.");

  dataFile = SD.open("data.txt", FILE_WRITE); // обязательно в блоке setup создаём файл на sd карте

  if (dataFile) {
    Serial.println("Файл успешно создан.");
    dataFile.close(); // Закрываем файл
  } else {
    Serial.println("Ошибка создания файла.");
  }

}


void loop() {
  // для начала нужно вывести и запомнить значение для каждой кнопки
  // Serial.println(analog);
  btn1.tick(keys.status(0));
  btn2.tick(keys.status(1));
  btn3.tick(keys.status(2));
  btn4.tick(keys.status(3));
  btn5.tick(keys.status(4));
  btn6.tick(keys.status(5));

  // забираем действия с кнопок
  //1
  if (btn1.click()) {drawBTNState("click 1");}
  if (btn1.held()) drawBTNState("held 1");
  //2
  if (btn2.click()) drawBTNState("click 2");
  if (btn2.held()) drawBTNState("held 2");
  //3
  if (btn3.click()) drawBTNState("click 3");
  if (btn3.held()) drawBTNState("held 3");
  //4
  if (btn4.click()) drawBTNState("click 4");
  if (btn4.held()) drawBTNState("held 4");
  //5
  if (btn5.click()) drawBTNState("click 5");
  if (btn5.held()) drawBTNState("held 5");
  //6
  if (btn6.click()) drawBTNState("click 6");
  if (btn6.held()) drawBTNState("held 6");

}