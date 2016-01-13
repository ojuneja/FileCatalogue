@echo off
echo ================== Project1: File Catalogue =======================
echo --------------------------------------------------------------------
echo  -------------------------------------------------------------------

echo ==================================================================================================================================================
echo TEST CASE 1: Demonstrating Requirement #3 and #4 by supplying path and one pattern along with option /s. Each filename and path is saved only once.
echo ==================================================================================================================================================
echo INPUT IS: . /s *.*
echo ===================
Debug\Executive.exe . /s *.*

echo ============================================================================================================================================
echo TEST CASE 2: Demonstrating Requirement #3 and #4 by supplying path and one pattern with no option. Each filename and path is saved only once.
echo ============================================================================================================================================
echo INPUT IS: . *.*
echo ================
Debug\Executive.exe . *.*

echo ========================================================================================================================================================
echo TEST CASE 3: Demonstrating Requirement 3# and #4 by supplying path and multiple patterns along with option /s. Each filename and path is saved only once.
echo ========================================================================================================================================================
echo INPUT IS: . /s *.h *.cpp
echo ========================
Debug\Executive.exe . /s *.h *.cpp

echo ================================================================================================
echo TEST CASE 4: Demonstrating Requirement #5 by supplying path with no pattern along with option /d
echo =================================================================================================
echo INPUT IS: . /d
echo ===============
Debug\Executive.exe . /d

echo ======================================================================================================
echo TEST CASE 5: Demonstrating Requirement #5 by supplying path and multiple patterns along with option /d
echo =======================================================================================================
echo INPUT IS: . /d *.tlog *.cpp
echo ============================
Debug\Executive.exe . /d *.tlog *.cpp

echo ======================================================================================================
echo TEST CASE 6: Demonstrating Requirement #6 by supplying path and multiple patterns along with option /f
echo ======================================================================================================
echo INPUT IS: . /f"Ojas Juneja" *.h *.cpp
echo ======================================
Debug\Executive.exe . /f"Ojas Juneja" *.h *.cpp

echo ================================================================================================
echo TEST CASE 7: Demonstrating Requirement #6 by supplying path and one pattern along with option /f
echo ================================================================================================
echo INPUT IS: . /fOjas *.*
echo =======================
Debug\Executive.exe . /fOjas *.*

echo ===================================================================================================================
echo TEST CASE 8: Demonstrating Requirement #3 and #5 by supplying path and multiple pattern along with option /s and /d
echo ===================================================================================================================
echo INPUT IS: . /s /d *.tlog *.cpp *.h
echo ==================================
Debug\Executive.exe . /s /d *.tlog *.cpp *.h

echo ==================================================================================================================
echo TEST CASE 9: Demonstrating Requirement #5 and #6 by supplying path with no pattern along with option /d and /fOjas
echo ==================================================================================================================
echo INPUT IS: . /d /fOjas
echo =====================
Debug\Executive.exe . /d /fOjas

echo ===============================================================================================================================
echo TEST CASE 10: Demonstrating Requirement #3,#5 and #6 by supplying path and multiple pattern along with option /s,/d and /fOjas
echo ==============================================================================================================================
echo INPUT IS: . /s /d /fOjas *.h *.cpp *.txt
echo ========================================
Debug\Executive.exe . /s /d /fOjas *.h *.cpp *.txt

echo =====================================================================================
echo TEST CASE 11: Demonstrating Requirement #7 by supplying no option on the command line
echo =====================================================================================
echo No Input is there
echo =================
Debug\Executive.exe

echo =========================================================================================================
echo TEST CASE 12: STEP1: Demonstrating Requirement #8 by supplying path and one pattern along with option /s.
echo TEST CASE 12: STEP2: User should continue for additional textsearch with valid format.
echo ========================================================================================================
echo INPUT IS: . /s /fdisplay *.*
echo =============================
Debug\Executive.exe . /s /fdisplay *.*
