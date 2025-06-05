include("/home/lasse/Dokumente/Programmieren/PasswordGenerator/build/Desktop-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/PasswordGenerator-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/lasse/Dokumente/Programmieren/PasswordGenerator/build/Desktop-Debug/PasswordGenerator
    GENERATE_QT_CONF
)
