<template>
	<div id="use_info">
		<div id="title">
			<span><h1>欢迎成为新用户 ! </h1></span>
			<span id="back">
				<i class="el-icon-back" @click="back">返回</i>
			</span>
		</div>
		<div id="info">
			<div>
				<label>账号名 :</label><br>
				<input type="text" v-model="acountName">
			</div>
			<div>
				<label>昵称 :</label><br>
				<input type="text" v-model="nicktName">
			</div>
			<div>
				<label>手机号 :</label><br>
				<input type="text" v-model="phone">
			</div>
			<div>
				<label>电子邮箱 :</label><br>
				<input type="text" v-model="email">
			</div>
			<div>
				<label>出生日期 :</label><br>
				<input type="date" v-model="birth">
			</div>
			<div>
				<label>验证码 :</label><br>
				<input type="text" v-model="validateCode">
				<button v-if="showTime" class="validateCode" @click="getValidate">{{ haveTime }}&nbsp;秒后重试</button>
				<button v-if="!showTime" class="validateCode" @click="getValidate">获取验证码</button>
			</div>
			<div>
				<label>密码 :</label><br>
				<input type="text" v-model="password">
			</div>
			<div>
				<label>确认密码 :</label><br>
				<input type="text" v-model="passwordConfirm">
			</div>
			<div id="regiter">
				<button @click="regiter">注 &nbsp;&nbsp;&nbsp;&nbsp; 册</button>
			</div>
		</div>
	</div>
</template>

<script>
	import axios,{Axios} from 'axios'
	export default{
		name:'Regiter',
		data() {
			return{
				acountName:'',
				nicktName:'',
				phone:'',
				email:'',
				password:'',
				passwordConfirm:'',
				birth:'',
				showTime:false,
				validateCode:'',
				getedvalidateCode:'',
				haveTime:0
			}
		},
		methods:{
			back(){
				this.$router.push({
					path:'/log'
				})
			},
			getValidate(){
				if(this.showTime==false){
					this.showTime=!this.showTime;
				}
				if(this.showTime==true){
					this.get();
					this.haveTime=10;
					var timer=setInterval(()=>{
						this.haveTime=this.haveTime-1;
						if(this.haveTime==0){
							clearInterval(timer);
							this.showTime=false;
						}
					},1000);
				}
			},
			get(){
			   console.log('获取---------');	
			   console.log(this.birth);
			   axios({
			   	url:'http://127.0.0.1:5000/user/register',
			   	method:'post',
			   	data:{
			   		type:'getCaptcha',
					email:this.email
			   	}
			   }).then((response)=>{
			
				  this.getedvalidateCode=response.data.captcha;
				  
			   }).catch(function(error){
			   	
			   });
			},
			regiter(){
				if(!this.acountName||!this.nicktName||!this.phone||!this.email||!this.validateCode||!this.password||!this.passwordConfirm){
					alert('信息不全，请继续完善 !');
				}
				else if(this.password!=this.passwordConfirm){
					alert('密码不一致，请检查数入 !');
				}
				else{
					console.log(this.validateCode,'   ',this.getedvalidateCode);
					if(this.validateCode!=this.getedvalidateCode){
					     alert('验证码不正确 ！');
					}else{
						axios({
							url:'http://127.0.0.1:5000/user/register',
							method:'post',
							data:{
								type:'register',
								validateCode:this.validateCode,
								acountName:this.acountName,// 账户
								nicktName:this.nicktName,//昵称 
								phone:this.phone,  // 手机号
								email:this.email,  // 邮箱
								birth:this.birth,
								password:this.password,// 密码
							}
						}).then((response)=>{
							console.log(response.data);
							if(response.data.status=='ok'){
								console.log('--------------- ok :  --',response.data);
								var select=confirm('您已成功注册账号 !');
								if(select){
									console.log('你点击了 确定 !',select);
									this.$router.replace({
										path:'/log'
									})
								}
							}else{
								alert('用户名或者昵称已存在 ！');
							}				
						}).catch(function(error){
							
						});
					}
				}
			}
		}
	}
</script>

<style scoped>
	#use_info{
		position: relative;
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		width: 60%;
		height: 100%;
		
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	#back{
		position: absolute;
		left: 30px;
		top: 20px;
	}
	#back i{
		font-size: 25px;
		color: blue;
	}
	#title{
		height: 8%;
	}
	h1{
		font-family: '幼圆';
	}
	#info{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		margin-top: 1.25rem;
		width: 80%;
		height: 80%;
		
		border: 2px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
	}
	#info>div{
		position: relative;
		width: 100%;
		margin-bottom: 1.25rem;
		
		/* border: 2px red solid; */
	}
	#info>div>label{
		position: relative;
		font-family: '幼圆';
		top: 30%;
		right: 40%;
	}
	#info>div>input{
		position: relative;
		top: 30%;
		right: 20%;
		width: 40%;
		height: 30px;
		border: none;
		border-bottom: solid purple 2px;
	}
	.validateCode{
		position: absolute;
		height: 30px;
		border: none;
		color: white;
		right: 38%;
		
		background-color: royalblue;
	}
	#regiter{
		position: relative;
		top: 60px;
		width: 50%;
	}
	#regiter>button{
		width: 50%;
		height: 1.875rem;
		font-size: 20px;
		color: white;
		background-color: royalblue;
	}
</style>