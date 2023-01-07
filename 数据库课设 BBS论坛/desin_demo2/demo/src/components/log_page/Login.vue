<template>
	<div id="ddd">
		<span id="content">
		   <span id="log_title">
			   <img id="logo" src="../../assets/icon/paperBird.png">
			   <span id="title">
				   <h3>只</h3>
				   <h3>为</h3>
				   <h3>遇</h3>
				   <h3>见</h3>
				   <h3>!</h3>
			   </span>
		   </span>
		   <span id="info">
			   <form>
				   <input id="useedit" type="text" placeholder="请输入账号" v-model="acountname">
				   <span v-if="showUseError" class="use_error">请输入账号 !</span>
				   <input id="passwordedit"  type="text" placeholder="请输入密码" v-model="password">
				   <span v-if="showPassordError" class="password_error">请输入密码 !</span>
				   <input id="sub" type="submit" value="Enter" @click.prevent="log">
					
					<router-link id="reg_link" to="/register">还没有账号?点击注册</router-link>
			   </form>
		   </span>
		</span>
	</div>
</template>

<script>
	import axios,{Axios} from 'axios'
	import pusub, { publish } from 'pubsub-js'
	
	export default {
		name:'Login',
		data(){
			return{
				acountname:'',
				password:'',
				
				showUseError:false,
				showPassordError:false
			}
		},
		methods:{
			log(){
				if(!this.acountname){
					
					this.showUseError=true;
					
					var timer=setTimeout(()=>{
						this.showUseError=false;
						clearTimeout(timer);
					},1000);
				}
				else if(!this.password){
					this.showPassordError=true;
					
					var timer=setTimeout(()=>{
						this.showPassordError=false;
						clearTimeout(timer);
					},1000);
				}
				else{
					// 管理员
					if(this.acountname=='manager'){
						this.$router.replace({
							name:'useraccountmag'
						})
					}
					else{ // 用户
						axios({
							url:'http://127.0.0.1:5000/user/log',
							method:'post',
							data:{
								acountname:this.acountname,
								password:this.password
							}
						}).then((response)=>{
							console.log(response.data);
							if(response.data.status=='ok'){
								console.log('用户信息正确 ！！！！！！');
								window.sessionStorage.setItem('acountname',this.acountname);
								window.sessionStorage.setItem('nickname',response.data.nickname);
								this.$router.replace({
									name:'mainfirstpage'
								});
							}
							else{
								alert('用户名或密码错误 !');
							}
						}).catch(function(error){
						
						})
					}
				}
			}
		}
	}
</script>

<style scoped>
	#ddd{
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		width: 100%;
		height: 100%;
		/* background-image: url('../../assets/backimg/bc2.jpg'); */
		background-repeat: no-repeat;
		background-size: cover;
		
		transform-style: preserve-3d;
		perspective: 100px;
		perspective-origin: 50% 50%;
	}
	#content{
		display: block;
		width: 500px;
		height: 400px;
		margin-top: 10%;
		
		/* animation: mov 1s 1; */
		perspective-origin: right top;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	
	@keyframes mov{
		0%{
			transform: translateX(800px);
		}
		100%{
			transform: translateX(0px);
		}
	}
	
	#log_title{
		position: relative;
		display: block;
		width: 20%;
		height: 100%;
		float: left;
		color: royalblue;
		/* background-color: aquamarine; */
		/* box-shadow: 0.3125rem 0.3125rem 0.3em black; */
		border-right: 2px solid gray;
	}
	h3{
		text-shadow: 5px 5px 0.1em black;
	}
	#logo{
		position: absolute;
		width: 100%;
		border-radius: 0.3125rem 0.3125rem ;
	}
	#title{
		position: absolute;
		top: 25%;
		left: 30%;
		font-family: '幼圆';
		font-size: 20px;
	}
	#info{
		width: 70%;
		height: 100%;
		float: left;
		/* background-color: rgba(124, 2, 125, 0.2); */
		border-radius: 0.3125rem;
	}
	form{
	    position: relative;
		width: 100%;
		height: 100%;
	}
	.use_error{
		position: absolute;
		display: block;
		
		top: 37%;
		right: 14%;
		font-size: 0.9375rem;
		color: red;
		background-color: yellow;
		height: 1.25rem;
		width: 60%;
		border-radius: 0.1875rem 0.1875rem;
		border: 0.0625rem red solid;
	}
	#useedit{
		position: absolute;
		width: 60%;
		top: 30%;
		border: none;
		right: 14%;
		text-align: left;
		font-size: 20px;
		color: gray;
		background-color: transparent;
		border-bottom: solid rebeccapurple 1px;
	}
	#passwordedit{
		position: absolute;
		width: 60%;
		top: 50%;
		border: none;
		right: 14%;
		text-align: left;
		font-size: 20px;
		color: gray;
		background-color: transparent;
		border-bottom: solid rebeccapurple 1px;
	}
	.password_error{
		position: absolute;
		display: block;
		
		top: 57%;
		right: 14%;
		font-size: 0.9375rem;
		color: red;
		background-color: yellow;
		height: 1.25rem;
		width: 60%;
		border-radius: 0.1875rem 0.1875rem;
		border: 0.0625rem red solid;
	}
	#sub{
		position: absolute;
		bottom: 10%;
		width: 70px;
		height: 70px;
		right: 4%;
		color: white;
		background-color: cornflowerblue;
		border-radius: 0.3125rem 0.3125rem;
	}
	#reg_link{
		position: absolute;
		font-size: 0.9375rem;
		text-decoration: none;
		bottom: 5%;
		right: 8%;
	}
</style>