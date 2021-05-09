set GN_DEFINES=is_official_build=true proprietary_codecs=true ffmpeg_branding=Chrome
set GN_ARGUMENTS=--ide=vs2019 --sln=cef --filters=//cef/*
call cef_create_projects.bat