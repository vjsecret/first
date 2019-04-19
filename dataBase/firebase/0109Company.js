class Employee{

	constructor(no,name,dept,salary){
			this.empno=no;
			this.empname=name;
			this.dept=dept;
			this.salary=salary;
			
			console.log("員編號工:" +this.empno +"<br>"+
						"員工姓名:" +this.empname +"<br>"+
						"員工部門:" +this.dept +"<br>"+
						"員工薪水:" +this.salary +"<br>");
		}	
}
Employee.prototype.showInfo=function(){
	return "員編號工:" +this.empno +"<br>"+
			"員工姓名:" +this.empname +"<br>"+
			"員工部門:" +this.dept +"<br>"+
			"員工薪水:" +this.salary +"<hr>";
};

var Person=function(){
		document.write("我是一個人<br>");
	};
Person.prototype.setName=function(name){
		this.name=name;
	};
Person.prototype.getName=function(){
		return this.name;
	};
	
var Sale=function(id,name){
	this.name=name;
	this.id=id;
	
	document.write("業務編號:" +this.id +"<br>"+
					"業務姓名:" +this.name +"<hr>");
}

var myHome={};

function desk(){
		return "這是一張桌子<br>";
	}
function mychair(str){
		return "這是:" +str +"椅子<br>";
	}

myHome.desk=desk;
myHome.chair=mychair;
myHome.Person=Person;