<template>
	<div class="msgd">
		<div class="uih">
			<label>与 ta 的聊天记录</label>
			<h3>{{ nickname }}</h3>
		</div>
		<div class="connn">
			<div v-for="(value,index) in msg" class="msgt">
				<div v-if="value.type=='r'" class="conLeft">
					<span>{{ value.content }}</span>
				</div>
				<div v-else class="conRight">
					<span>{{ value.content }}</span>
				</div>
			</div>
		</div>
		<div class="send">
			<textarea v-model="sendCont" placeholder="输入发送内容"></textarea>
			<button @click="sendMsg">发送</button>
		</div>
	</div>
</template>

<script>
	import axios from 'axios'
	
	export default{
		name:'MsgDetail',
		data() {
			return{
				nickname:this.$route.query.nickname,
				sendCont:'',
				msg:[
				]
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/user/userchat',
				method:'post',
				data:{
					reciever:this.nickname,
					sender:window.sessionStorage.getItem('nickname')
				}
				
			}).then((response)=>{
				this.msg=response.data.userchat;
			}).catch(function(error){
				
			})
		},
		methods:{
			sendMsg(){
				console.log(this.nickname,'发送消息 : ',this.sendCont);
				var mes1 = {
						type:'s',
						content: this.sendCont,
						posttime: '2022-1-11',
						keynum: 0
				}
				this.msg.push(mes1);
				this.sendCont='';
				
				axios({
					url:'http://127.0.0.1:5000/user/sendmessage',
					method:'post',
					data:{
						reciever:this.nickname,
						sender:window.sessionStorage.getItem('nickname'),
						content:mes1.content
					}
					
				}).then((response)=>{
					
				}).catch(function(error){
					
				})
			}
		}
	}
</script>

<style scoped>
	.msgd{
		position: relative;
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 80%;
		height: 100%;
		overflow: auto;
		border: 3px purple solid;
		border-radius: 0.3125rem 0.3125rem;
	}
	.uih{
		position: absolute;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		top: 0;
		width: 100%;
		height: 2.875rem;
		background-color: aquamarine;
	}
	.uih label{
		position: absolute;
		left: 10px;
		color: gray;
	}
	.connn{
		overflow: auto;
		
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		margin-top: 2.5rem;
	}
	.msgt{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
	}
	.send{
		position: absolute;
		bottom: 0;
		
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		margin-top: 1.25rem;
		width: 100%;
		height: 2.5rem;
	}
	textarea{
		flex: 6;
		height: 100%;
	}
	button{
		flex: 1;
		height: 100%;
		background-color: royalblue;
		color: white;
	}
	
	.conLeft{
		display: flex;
		width: 100%;
		height: auto;
		padding: 0.3125rem;
		
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
	}
	.conRight{
		display: flex;
		width: 100%;
		height: auto;
		padding: 0.3125rem;
		
		justify-content: flex-end;
		align-items: center;
	}
	
	span{
		overflow: auto;
		background-color: royalblue;
		color: white;
		padding: 0.3125rem;
		border-radius: 0.3125rem 0.3125rem;
	}
	.conRight span{
		overflow: auto;
		background-color: green;
		color: white;
		padding: 0.3125rem;
		border-radius: 0.3125rem 0.3125rem;
	}
</style>