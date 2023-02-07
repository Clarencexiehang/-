<template>
	<div class="dinfo">
		<div class="info">
			<span>
				用户名 : 
				<input class="inf" type="text" disabled :value="user.nickname">
			</span>
			<span>
				账号 : 
				<input class="inf" type="text" disabled :value="user.acountname">
			</span>
			<span>
				电话 : 
				<input class="inf" type="text" disabled :value="user.phone">
			</span>
			<span>
				邮箱 : 
				<input class="inf" type="text" disabled :value="user.email">
			</span>
			<span>
				生日 : 
				<input class="inf" type="text" disabled :value="user.birthday">
			</span>
			<span>
				密码 : 
				<input class="inf" type="text" disabled :value="user.password">
			</span>
		</div>
	</div>
</template>

<script>
	import axios from 'axios'
	export default{
		name:'DetailInfo',
		data() {
			return{
				user:{
					nickname:'loading...',
					acountname:'loading...',
					phone:'loading...',
					email:'loading...',
					birthday:'loading...',
					password:'loading...'
				}
			}
		}, 
		methods:{
			get(nickname){
				console.log('获取用户名 ',nickname);
				axios({
					url:'http://127.0.0.1:5000/user/modify',
					method:'post',
					data:{
						type:'get',
						nickname:nickname
					}
				}).then((response)=>{
					console.log(response.data);
					this.user.nickname=response.data.newuser.nickname;
					this.user.acountname=response.data.newuser.acountname;
					this.user.email=response.data.newuser.email;
					this.user.birthday=response.data.newuser.birthday;
					this.user.phone=response.data.newuser.phone;
					this.user.password=response.data.newuser.password;				
				}).catch((error)=>{
					
				})
			}
		},
		beforeMount() {
			this.$bus.$on("getNickname",this.get);
		}
	}
</script>

<style scoped>
	.dinfo{
		flex: 3;
		height: 100%;
		margin-left: 0.625rem;
		overflow: auto;
		
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	.info{
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		width: 50%;
		height: 50%;
	}
	span{
		width: 100%;
		margin-top: 1.25rem;
		color: white;
		font-size: 1.45rem;
	}
	.inf{
		height: 3.125rem;
		border: none;
		border-bottom: 2px purple solid;
	}
	input{
		color: blue;
		background: transparent;
		color: red;
		font-size: 1.25rem;
		text-align: center;
	}
</style>