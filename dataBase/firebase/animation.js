	var i=0;
	var j;
	var flag=false;
	function wonwon(){
		str="";
		if(i<9){
			i++; //i=i+1;
			str="dog000" + i;
		}else if(i<68){
			i++; //i=i+1;
			str="dog00" + i ;
		}else{
			i=1;
			str="dog000" + i ;
		}
		
		document.getElementById('imgShow').src="images/" + str  + ".png";
		document.getElementById('animation').innerHTML="第 " + i + " 張 : " + str ;
		
		}
		if(flag){
			j=window.setInterval(wonwon,42);
			
		}
		
		function ssDog(){
			if(!flag){				
				j=window.setInterval(wonwon,42);
				document.getElementById('btn').innerHTML="STOP";
				flag=true;
				}else
				{
				window.clearInterval(j);
				document.getElementById('btn').innerHTML="PLAY";
				flag=false;
				}
			}
/*var tmp=window.setInterval(showCurrentTime,42);
	
	var i=1;
	var str='';
	function showCurrentTime(){	
			if (i<10){
				str="0"+i;
			}
			else
				str=i;

			document.getElementById('animation').innerHTML="第"+i+"張圖片:dog00"+str+".png";
			document.getElementById('imgShow').src="images/dog00"+str+".png";
				
			if (i<68)
				i++;
			else
				i=1;
	}*/