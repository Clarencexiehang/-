<template>
	<div class="post">
		<textarea cols="30" rows="10" placeholder="请输入公告内容" v-model="NoticeContent"></textarea>
		<br>
		<button @click="PostNotice">发&nbsp;布&nbsp;公&nbsp;告</button>
	</div>
</template>

<script>
	import axios from 'axios'
	export default{
		name:'PostNotice',
		data() {
			return{
				NoticeContent:''
			}
		},
		methods:{
			PostNotice(){
				if(!this.NoticeContent){
					alert('请输入公告内容 !');
				}
				else{
					console.log('发布公告: ',this.NoticeContent);
					var HasPost=confirm('已发布公告 !');
					axios({
						url:'http://127.0.0.1:5000/admin/postnotice',
						method:'post',
						data:{
							NoticeContent:this.NoticeContent
						}
					}).then((response)=>{
						console.log(response.data);
						
					}).catch((error)=>{
						
					})
					
					if(HasPost){
						this.NoticeContent=null;
					}
					
				}
			}
		}
	}
</script>

<style scoped>
	.post{
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		width: 100%;
		height: 100%;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	textarea{
		width: 80%;
		height: 50%;
		font-size: 1.25rem;
	}
	button{
		width: 20%;
		height: 2.575rem;
		background-color: blueviolet;
		margin-top: 3.125rem;
		color: white;
		font-size: 1.25rem;
	}
</style>