<template>
	<div class="uae">
		<div class="title">
			标题 : <input type="text" placeholder="请输入标题" v-model="title">
		</div>
		<div class="content">
			<span>内容 :</span>
			<span>
				<textarea placeholder="请输入内容" v-model="content"></textarea>
			</span>
		</div>
		
		<button class="cancel" @click="back">返回</button>
		<button class="mos" @click="postArt">确认发布</button>
	</div>
</template>

<script>
	import axios from 'axios'
	
	export default{
		name:'PostArticle',
		data() {
			return{
				title:'',
				content:''
			}
		},
		methods:{
			back(){
				this.$router.back();
			},
			postArt(){
				axios({
					url:'http://127.0.0.1:5000/article/postarticle',
					method:'post',
					data:{
						acountname:window.sessionStorage.getItem('acountname'),
						title:this.title,
						content:this.content
					}
				}).then((response)=>{
					console.log(response.data);
					alert('文章发布成功 !');
					this.title='';
					this.content='';
				}).catch(function(error){
				
				})
				
				
			}
		}
	}
</script>

<style scoped>
	.uae{
		display: flex;
		width: 50%;
		height: 100%;
		overflow: auto;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		border-radius:5px 5px;
		border: 2px purple solid;
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