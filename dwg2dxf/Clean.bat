@echo Off
echo  按任意键开始删除文件
pause
del /s /a *.sdf *.ipch *.obj *.lib *.exe *.pch *.tlog *.suo *.ncb *.user *.dll *.pdb *.netmodule *.aps *.ilk  *.clw *.opt *.plg 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\x64" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\Debug" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\Release" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\Obj" 2>nul
FOR /R . %%d IN (.) DO rd /s /q "%%d\ipch" 2>nul
rem If the Properties directory is empty, remove it
FOR /R . %%d in (.) do rd /q "%%d\Properties" 2> nul
