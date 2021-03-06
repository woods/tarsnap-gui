#include "translator.h"
#include "debug.h"

#include <QLibraryInfo>

Translator::Translator() : _qtTranslator(nullptr), _appTranslator(nullptr)
{
    _languageMap["English"]  = "en";
    _languageMap["Romanian"] = "ro";
}

Translator &Translator::instance()
{
    static Translator instance;
    return instance;
}

void Translator::translateApp(QApplication *app, QString lang)
{
    if(!app)
        return;

    DEBUG << "System language is "
          << QLocale::languageToString(QLocale().language());

    if(lang == LANG_AUTO)
        lang = QLocale::languageToString(QLocale().language());

    if(_languageMap.find(lang) == _languageMap.end())
        return;

    if(_qtTranslator && _appTranslator)
    {
        app->removeTranslator(_qtTranslator);
        app->removeTranslator(_appTranslator);
        delete _qtTranslator;
        _qtTranslator = nullptr;
        delete _appTranslator;
        _appTranslator = nullptr;
    }

    _qtTranslator = new QTranslator();
    _qtTranslator->load("qt_" + _languageMap[lang],
                        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app->installTranslator(_qtTranslator);

    _appTranslator = new QTranslator();
    _appTranslator->load("tarsnap-gui_" + _languageMap[lang], ":/translations");
    app->installTranslator(_appTranslator);
}

QStringList Translator::languageList()
{
    return _languageMap.keys();
}
