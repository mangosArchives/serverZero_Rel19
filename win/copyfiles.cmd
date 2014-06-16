echo ******************************************************
echo ** COPY STEP                                        **
echo ******************************************************

echo .
echo **********************
echo ** Source Path      **
echo **********************
echo Source: %1

echo .
echo **********************
echo ** Destination Path **
echo **********************
echo Destination: %2

echo .
echo **********************
echo ** Current Path     **
echo **********************
cd

echo .
echo **********************
echo ** DLL's            **
echo **********************
copy ..\%1\*.dll %2

echo .
echo **********************
echo ** mangosd.conf     **
echo **********************
copy ..\..\src\mangosd\mangosd.conf.dist.in %2

echo .
echo **********************
echo ** ahbot.conf       **
echo **********************
copy ..\..\src\game\AuctionHouseBot\ahbot.conf.dist.in %2

echo .
echo **********************
echo ** Extraction Tools **
echo **********************
copy ..\..\src\tools\Extractor_Binaries\*.* %2

echo .
echo **********************
echo **  OpenSSL DLL's   **
echo **********************
copy ..\..\dep\lib\libeay32.dll %2
copy ..\..\dep\lib\ssleay32.dll %2
copy ..\..\dep\lib\\libssl32.dll %2

echo .
echo **********************
echo **   MySQL DLL's    **
echo **********************
copy ..\..\dep\lib\libmysql.dll %2

echo .
echo **********************
echo * Copy Step Complete *
echo **********************
