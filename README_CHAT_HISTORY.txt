# Full Duplex GUI Chat - Chat History Version

تم تعديل المشروع ليحفظ الشات تلقائيًا في ملف نصي.

## الملفات المعدلة

- `Full duplex_client_gui/main.cpp`
- `Full duplex_server_gui/main.c`

## طريقة الحفظ

كل رسالة يتم إرسالها أو استقبالها تتسجل في ملف:

```txt
chat_history.txt
```

الملف يتعمل تلقائيًا في نفس فولدر تشغيل البرنامج، غالبًا داخل:

```txt
bin/Debug
```

## شكل السجل

```txt
[2026-04-27 16:55:00] Client: hello
[2026-04-27 16:55:04] Server: hi
```

## ملاحظات

- تم تجاهل الرسائل الفارغة، يعني لو ضغطت Send من غير كلام مش هيتبعت ولا يتحفظ.
- لو شغلت client و server من فولدرين مختلفين، كل برنامج هيعمل ملف `chat_history.txt` عنده.
- افتح المشروع من Code::Blocks واعمل Build/Run عشان يطلع exe جديد بالتعديل.
