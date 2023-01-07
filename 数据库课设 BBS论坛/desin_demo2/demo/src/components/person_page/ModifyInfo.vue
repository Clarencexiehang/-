<template>
	<div id="baseInfo">
		<span id="headphoto">
			<img :src="useInfo.headpath" alt="当前头像" title="当前头像">
		</span>
		<span id="useinfo">
			<form>
				<div>
					账号 : &nbsp;&nbsp;&nbsp;<input id="acount" type="text" v-model="useInfo.acountname" disabled="true">
				</div>
				<div>
					昵称 : &nbsp;&nbsp;&nbsp;<input id="nickname" type="text" v-model="useInfo.nickname">
				</div>
				<div>
					手机号 : &nbsp;&nbsp;<input id="phone" type="text" v-model="useInfo.phone">
				</div>
				<div>
					邮箱 : &nbsp;&nbsp;&nbsp;&nbsp;<input id="email" type="text" v-model="useInfo.email">
				</div>
				<div>
					密码 : &nbsp;&nbsp;&nbsp;&nbsp;<input id="password" type="text" v-model="useInfo.password">
				</div>
				<input type="button" id="ok" @click="MakeModify" value="确认修改">
			</form>
		</span>
	</div>
</template>

<script>
	import axios from 'axios';
	export default{
		name:'ModifyInfo',
		data() {
			return{
				useInfo:{
					nickname:window.sessionStorage.getItem('nickname'),
					acountname:window.sessionStorage.getItem('acountname'),
					phone:'c',
					email:'d',
					password:'e',
					headpath:''
				}
			}
		},
		beforeMount() {
			console.log('请求---------------');
			axios({
				url:'http://127.0.0.1:5000/user/modify',
				method:'post',
				data:{
					type:'get',
					nickname:this.useInfo.nickname
				}
			}).then((response)=>{
				console.log(response.data);
				this.useInfo.nickname=response.data.newuser.nickname;
				this.useInfo.phone=response.data.newuser.phone;
				this.useInfo.email=response.data.newuser.email;
				this.useInfo.password=response.data.newuser.password;
				
			}).catch((error)=>{
				
			})
		},
		methods: {
		    MakeModify(){
				axios({
					url:'http://127.0.0.1:5000/user/modify',
					method:'post',
					data:{
						type:'modify',
						useInfo:this.useInfo
					}
				}).then((response)=>{
					console.log(response.data);
					if(response.data.status=='ok'){
						alert('修改成功 !');
						window.sessionStorage.setItem('nickname',this.useInfo.nickname);
						location.reload();
						this.$router.replace({
							name:'article'
						})
					}
					else{
						alert('修改异常 !');
					}
				}).catch(function(error){
					
				})
				
				
			}
		}
	}
</script>

<style scoped>
	#baseInfo{
		display: flex;
		flex-direction: column;
		justify-content: space-evenly;
		align-items: center;
		
		width: 100%;
		height: 100%;
		background-color: white;
	}
	#headphoto{
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		border: 2px dashed gray;
		width: 11.5rem;
		height: 11.5rem;
	}
	#useinfo{
		display: block;
		width: 50%;
		height: 50%;
	}
	form{
		display: flex;
		flex-direction: column;
		justify-content: space-between;
		align-items: center;
		
		width: 100%;
		height: 100%;
	}
	form div{
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		height: 20%;
		font-size: 1.25rem;
		color: orange;
	}
	input :not(#ok){
		height: 100%;
	}
	#acount,#nickname,#phone,#email,#password{
		width: 12.5rem;
		height: 1.875rem;
		border: none;
		border-bottom: 0.125rem solid gray;
	}
	#ok{
		width: 20.5rem;
		height: 2.875rem;
		border: none;
		font-size: 1.25rem;
		color: white;
		background-color: palevioletred;
		border-radius: 0.1875rem 0.1875rem;
	}
</style>