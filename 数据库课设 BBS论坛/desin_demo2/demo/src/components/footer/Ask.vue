<template>
	<div id="ask_div">
		<div id="title">
			<h1>解决你的疑问</h1>
		</div>
		<div id="content_div">
			<div id="log">
				<div v-for="(msgObj,index) in com_log" class="item">
					<span v-if="msgObj.type=='user'" class="user_content">
						{{ msgObj.msg }}
					</span>
					<span v-else class="manager_content">
						{{ msgObj.msg }}
					</span>
				</div>
			</div>
			<div id="send">
				<span>
					<textarea id="comunite" placeholder="输入聊天内容" v-model="content" cols="30" rows="10"></textarea>
					<button @click="send">发 &nbsp;&nbsp;送</button>
				</span>
			</div>
		</div>
	</div>
</template>

<script>
	export default{
		name:'Quest',
		data() {
			return{
				content:'',
				com_log:[
					{
						type:'user',
						msg:'你好 ！'
					},
					{
						type:'manager',
						msg:'Hello World ！'
					}
				]
			}
		},
		methods:{
			sendSuggest(){
				alert('发出成功 !');
			},
			send(){
				if(this.content){
					var replay={
						type:'user',
						msg:this.content
					};
					this.com_log.push(replay)
					this.content='';
					
					var timer=setTimeout(()=>{
						this.replay();
						clearTimeout(timer);
					},1000);
					
				}
			},
			replay(){
				var replay={
					type:'manager',
					msg:'Hello World ！'
				};
				this.com_log.push(replay)
			}
		},
		
	}
</script>

<style scoped>
	#ask_div{
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		width: 100%;
		height: 100%;
		/* background-color: steelblue; */
	}
	h1{
		font-family: '幼圆';
	}
	#content_div{
		position: relative;
		width: 60%;
		height: 100%;
		margin-top: 0.625rem;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
		
		margin-top: 1%;
		overflow: auto;
	}
	#log{
		width: 100%;
		height: 90%;
		overflow-y: auto;
		overflow: scroll;
	}
	.item{
		position: relative;
		width: 99%;
		padding: 0.625rem;
		height: auto;
		
		margin-top: 20px;
		/* border: 2px red solid; */
	}
	.user_content{
		position: absolute;
		background-color: royalblue;
		color: white;
		right: 1.125rem;
		padding: 0.3125rem;
		border-radius: 0.1875rem 0.1875rem;
	}
	.manager_content{
		position: absolute;
		background-color: royalblue;
		color: white;
		left: 0.125rem;
		padding: 0.3125rem;
		border-radius: 0.1875rem 0.1875rem;
	}
	#send{
		position: absolute;
		display: flex;
		flex-direction: row;
		justify-content: flex-end;
		align-items: center;
		
		width: 99%;
		height: 10%;
		bottom: 0;
		background-color: bisque;
	}
	#comunite{
		height: 2.125rem;
		width: 20.5rem;
		margin-left: 20px;
		font-size: 0.9375rem;
	}
	button{
		height: 2.125rem;
		width: 12.5rem;
		background-color: cornflowerblue;
		color: white;
		font-size: 20px;
		border-radius: 0.1875rem 0.1875rem;
	}
</style>