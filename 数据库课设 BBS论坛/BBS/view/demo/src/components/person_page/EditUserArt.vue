<template>
	<div class="uae">
		<div class="title">
			标题 : <input type="text" v-model="title">
		</div>
		<div class="content">
			<span>内容 :</span>
			<span>
				<textarea v-model="content"></textarea>
			</span>
		</div>
		
		<button class="cancel" @click="cancel">取消修改</button>
		<button class="mos" @click="modifyArt">确认修改</button>
	</div>
</template>

<script>
	import axios from 'axios'
	
	export default{
		name:'EditUserArt',
		data() {
			return{
				article_id:'',
				title:'',
				content:''
			}
		},
		beforeMount() {
			this.article_id=this.$route.query.article_id;
			axios({
				url:'http://127.0.0.1:5000/user/getart',
				method:'post',
				data:{
					article_id:this.article_id
				}
			}).then((response)=>{
				console.log(response.data);
				this.title=response.data.art.title;
				this.content=response.data.art.content;
			}).catch(function(error){
			
			})
		},
		methods:{
			cancel(){
				this.$router.replace({
					name:'article'
				})
			},
			modifyArt(){
				axios({
					url:'http://127.0.0.1:5000/user/modifyart',
					method:'post',
					data:{
						article_id:this.article_id,
						title:this.title,
						content:this.content
					}
				}).then((response)=>{
					console.log(response.data);
					this.$router.replace({
						name:'article'
					})
				}).catch(function(error){
				
				})
				
				
			}
		}
	}
</script>

<style scoped>
	.uae{
		display: flex;
		width: 60%;
		height: 100%;
		overflow: auto;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		border: 2px red solid;
	}
	.title{
		width: 80%;
	}
	input{
		width: 80%;
		height: 2.5rem;
		color: red;
		font-size: 1.875rem;
	}
	.content{
		width: 90%;
		height: 100%;
		margin-top: 0.625rem;
	}
	textarea{
		width: 70%;
		height: 100%;
	}
	.cancel{
		width: 25rem;
		height: 2.5rem;
		background-color: green;
		color: white;
		font-size: 1.25rem;
		margin-top: 3.75rem;
		margin-bottom: 1.75rem;
	}
	.mos{
		width: 25rem;
		height: 2.5rem;
		margin-bottom: 2.25rem;
		background-color: red;
		color: white;
		font-size: 1.25rem;
	}
</style>