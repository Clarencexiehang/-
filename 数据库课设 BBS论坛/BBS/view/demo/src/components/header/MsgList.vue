<template>
	<div class="msgl">
		<div class="usersend">我的消息</div>
		<div v-if="msgIsNull" class="nocom">无聊天记录 !</div>
		<div v-else class="com">
			<div v-for="(value,index) in msg" class="msgitem" @click="enterCom(value.sender)">
				<div class="ii">{{ value.sender }}</div>
				<div class="cc">
					{{ value.content }}
				</div>
				<div class="tt">
					<span class="txt">{{ value.posttime }}</span>
					<button class="clr" @click.stop="clearCom(index,value.sender_ac)">清除聊天</button>
				</div>
			</div>
		</div>
	</div>
</template>

<script>
	import axios from 'axios'
	
	export default{
		name:'MsgList',
		data() {
			return{
				msg:[
				],
				msgIsNull:true
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/user/reciverdata',
				method:'post',
				data:{
					reciever:window.sessionStorage.getItem('acountname')
				}
			}).then((response)=>{
				this.msg=response.data.mymessage;
				if(this.msg.length!=0){
					this.msgIsNull=false;
				}
			}).catch(function(error){
			
			})
		},
		methods:{
			enterCom(nickname){
				this.$router.push({
					name:'msgdetail',
					query:{
						nickname:nickname
					}
				})
			},
			clearCom(index,sender_ac){
				console.log('------- 清空与 ',sender_ac,' 的聊天记录');
				this.msg.splice(index,1);
				
				//  清空数据库
				axios({
					url:'http://127.0.0.1:5000/user/clrmsg',
					method:'post',
					data:{
						sender:sender_ac,
						reciever:window.sessionStorage.getItem('acountname')
					}
				}).then((response)=>{
					
				}).catch(function(error){
				
				})
			}
		}
		
	}
</script>

<style scoped>
	.msgl{
		position: relative;
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 80%;
		height: 100%;
		overflow: auto;
		border: 2px purple solid;
		border-radius: 5px 5px;
	}
	.usersend{
		position: absolute;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		top:0;
		width: 100%;
		height: 50px;;
		background-color: royalblue;
		border-radius: 5px 5px;
		
		color:white;
		font-size: 20px;
	}
	.msgl .msgitem:first-of-type{
		margin-top: 75px;
	}
	.msgitem{
		margin-top: 0.625rem;
		width: 90%;
		height: 6.125rem;
		padding: 1.25rem;
		border-radius: 5px 5px;
		background-color: white;
	}
	.ii{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		border-bottom: 2px gray solid;
	}
	.cc{
		color: gray;
		margin-top: 20px;
		margin-bottom: 20px;
	}
	.tt{
		position: relative;
		
		display: flex;
		flex-direction: row;
		justify-content: flex-end;
		align-items: center;
		color: gray;
		margin-right: 0.625rem;
	}
	.txt{
		position: absolute;
		right: 15%;
		top: 15%;
	}
	.clr{
		position: absolute;
		
		right: 1%;
		top: 15%;
		background-color: transparent;
		color: red;
		background-color: cadetblue;
		font-size: 15px;
	}
	.nocom{
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		width: 100%;
		height: 100%;
		color: red;
		font-size: 1.875rem;
		font-family: '幼圆';
	}
	.com{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		height: 100%;
	}
</style>