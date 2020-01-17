set RESULTS_FILE=release.win32.tests.txt

echo '----- Test Results -----' >  %RESULTS_FILE% 
for %%f in (*test*.exe) do (
    echo '----- Execute %%f -----' >> %RESULTS_FILE% 
    %%~f >> %RESULTS_FILE%
    echo '----- Done -----' >> %RESULTS_FILE%
)
  
