# HEIC / Image to JPEG Converter (Qt)

Простое кроссплатформенное GUI-приложение на **Qt 6 (C++)** для конвертации изображений (HEIC, WEBP, PNG, JPG и др.) в **JPEG**.

Проект разработан и собирается в **Qt Creator 16.0.1**
на базе **Qt 6.8.2 (GCC 14.2.0)**.

---

## 🚀 Возможности

* ✅ Поддержка форматов:
  
  * HEIC
  * AVIF
  * WEBP
    
* ✅ Выбор:

  * отдельного файла
  * целой папки
* ✅ Пакетная обработка изображений
* ✅ Лог выполнения в интерфейсе
* ✅ Настройка качества JPEG
* ✅ Поддержка Unicode-путей (кириллица, пробелы и т.д.)

---

## 🖥️ Интерфейс

* Выбор источника (файл или папка)
* Выбор папки назначения
* Кнопки **Start / Stop**
* Окно логов
* Окно настроек

---

## 🛠️ Сборка проекта

### Требования

* **Qt 6.8.2**
* **Qt Creator 16.0.1**
* Компилятор **GCC 14.2.0** (MinGW / Linux)
* Поддержка формата HEIC:

  * `libheif`
  * HEVC backend (если требуется)

---

### 📦 Сборка через `.pro` (qmake)

Проект **НЕ использует CMake**.

или просто:

1. Открыть `.pro` файл в Qt Creator
2. Выбрать нужный Kit
3. Нажать **Build → Run**

---

## 📁 Структура проекта

```text
.
├── main.cpp
├── mainwindow.h
├── mainwindow.cpp
├── heicconverter.h
├── heicconverter.cpp
├── settingsdialog.h
├── settingsdialog.cpp
├── clickablelabel.h
├── clickablelabel.cpp
├── resources.qrc
├── *.ui
└── project.pro
```

---

## ⚙️ Используемые технологии

* **Qt Widgets**
* **QImage / QImageReader**
* **QThread**
* **libheif** (для HEIC)
* **C++17**

---

> Все изображения конвертируются **в JPEG**

---

## ❗ Возможные проблемы

* HEIC может не открываться, если `libheif` собран без HEVC
* WEBP требует Qt Image Plugins
* На Windows (MinGW) убедись, что DLL находятся рядом с `.exe`

---

## 📄 Лицензия

GPL-3.0
