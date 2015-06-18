macx {
    dispParaFiles.files = config/para.json
    dispParaFiles.path = Contents/Resources
    QMAKE_BUNDLE_DATA += dispParaFiles
}

win32 {
    dispParaFiles.files = config/para.json
    dispParaFiles.path = $$OUT_PWD/config
    INSTALLS += dispParaFiles
}
