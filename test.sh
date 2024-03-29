make
function runtest(){
	msg=`diff a b`
	if [[ $msg != "" ]]; then
		echo "Test Failed"
		echo $msg
	else
		echo "passed"
	fi
}

echo "testing case 1"
./SHA3 HelloWorld 512 > a
echo -n "8051E75A0819AFED889A9812C3713380684DAF07C4F073C63EAC7A863B02343DE0C20FECD248CB5031A6230F21602D8DE9972D1BA010D8CE294784ED91AB38C8" > b
runtest;

echo "testing case 2"
./SHA3 ILoveCryptography 2000 >a
echo -n "F846F11C13B050457F22D2BFA0A835EFF2EE76F8007719B81E94EC29B2802167D52C0678C27AF664C4F0AB6CC893CDEAAE4B0BDD7D864BFE44B37F526B40E568792EBAE28D8A7F95FA1A45F128F099D4B10980795422074940A55AA8269360B182D5C2099889D3889A1A4661ED86E0986FE25724EE12EB6857158B77DA9C9D424D0358108EC45E08C2F7369F0A23ABB765170D70FA606D94E28922A71B56ADD4D434C80AFB43023DEF70C8B41C7DAAA7AF10416C5072D001A7195E4B942ED9D7C964A7D93F847C82C78A7C9AD2AE73E0332CAFC631AB0157AB0ADE1BF3599DF519CA7DC369069D62B5927102C0418E856460324AD38AFA991F95" > b
runtest;

echo "testing case 3"
./SHA3 Atreeconstructedbyhashingpaireddatatheleavesthenpairingandhashingtheresu 800 > a
echo -n "D4EF2F8C28B17F67935B564750FDA6D2FD5751BA8DD66D768D81FD4B48C977392B5EB1551548BBAB844A9304C4A7944F66F0ADF6747B989FE2D0B260A968663403E8B5FE880D8DAD50A7F1A2F50197A77DA145BC4D05004D4FE4877680051E988EF9E489" > b
runtest;

echo "testing case 4"
./SHA3 AjudgeinBrazilorderedonMondaythatphonecompaniesblockFacebooksmessagingserviceWhatsAppthroughoutthecountryfor72hoursinresponsetoitsrefusaltocooperateinapoliceinvestigationJudgeMarcelMontalvaodeliveredtheorderbecauseWhatsAppwouldnotturnoverinformationthatcouldrelatetoaninvestigationintonarcoticsactivityandaninterstategangThebanwillgointoeffectat2pmlocaltimeBloombergreportsandthefinetophonecompaniesfornotblockingtheappwouldbeabout143000perdayRoughlyhalfofBrazilspopulationof200millionusesthemessagingserviceasaneconomicalalternativetootherpricierformsofcommunicationsotheshutdownwillhaveabigeffectonmanyBraziliansThisisthesecondtimeinsixmonthsajudgehassuspendedtheserviceinBrazilthoughacourtoverturnedthepreviousdecisioninDecember 3000 >a

echo -n "8B57D6ACFCA35EBBE2D7083E86AC731F481DE6207F576F6AE4E56D68B45D2B842CA4AA20B995CFB65790B6D09F9BC78A72BFB83C1FA8B4489A89237EA6EBD769BB67D8A793BA2D21BE47FA1BD8D787CF983A661D85D2D5E02FD3082819051AF23C222F23AA4305303380E365CF83E4955B42766AD26F84AD4B5A436E6E3BE4AD6E38AFF28EF08F1C996133EE3196D0A387BAA9C7A4389476CD623207DEC105397DE9D9FBCD20552058D6E1E5D2D5F20EB31FE6E746272113C870E3304986B9DF4E8F8192FAE8CE31337DFBFBA16C5E3DB974A283C84EEB9BF1421C626BE806EA1B928D5F48118E328254F000A4EE5456353F136679FBBFF0454D62258FBC86FE235E6F937C66A2B7E3145217DD1856D8F7B53D0E629E71430DD7BFD09BEDCF4B9823AFA8ADE7EFEED5F66AA830664CB179670D569FB0E1A7917E54141DF17436E9E6AFE233B1E51155CFBE31A78127274809BD56CFFDA06AC96AF9371C998395D8560A3A9530A75F9D5F538A6106ACB44BD9AB73DF5CC5" >b
runtest;

rm -f a b
