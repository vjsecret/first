// JavaScript Document
function sloganLength(slogan){
	return "slogan長度為:" + slogan.length +"字元!"
}
function searchStr(str,searchWord){
	var index=0;
	index=str.indexOf(searchWord);
	if (index<0){
		return "無"+searchWord +"字串";
	}
	else{
		return "「"+searchWord+"」由"+str+"中的第"+ (index+1) +"個字元開始";
	}
}
function spitWord(str){
	if (typeof(str)==="string" && str!=""){
		var words = str.split(' ');
		var result='';
		for (var i=0;i<words.length;i++){
			result=result+"第"+(i+1)+"個字:"+words[i]+"<br>";
		}
	}
	else{
		result="無法分割";
	}
	return result
}
function changePicture(imgfile){
//	//demo.innerHTML=imgfile
//	//imgfile.scr="images/jspic/on.gif";
//	var str=imgfile.src;
//	//var str=imgfile;
//	var words = str.split('/');	
//	//demo.innerHTML=words[words.length-1];
//	if (typeof(str)==="string" && str!=""){
//		if (words[words.length-1]=="off.gif"){
//			//return "on.gif"
//			imgfile.src="images/jspic/on.gif";
//			}
//			else{
//				//return "off.gif"
//				imgfile.src="images/jspic/off.gif";
//			}
//		}

	if (imgfile.src.match("on"))
		imgfile.src="images/jspic/off.gif";
	else
		imgfile.src="images/jspic/on.gif";
}
function typeWord(str,obj){
	if (count<=str.length){
			demo.innerHTML=str.substring(0,count)
			count++;
		}
		else{
			count=0;
		}
}