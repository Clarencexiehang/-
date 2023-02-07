<template>
	<div id="artcle_item">
		<div class="art_data" v-for="(item,index) in Article" :key="index">
			<div class="decde">
				<h3>{{ item.title }}</h3>
				<div>
					{{ item.content }}
				</div>
			</div>
			<div class="score">
				<span>
					发表时间 : {{ item.posttime }}
				</span>
				<span>
					<i class="el-icon-s-opportunity" title="点赞">{{ item.agreenum }}</i>
				</span>
				<button @click="reEdit(item.article_id,item.title)">重新编辑</button>
				<button @click="remove(index,item.article_id,item.title)">删除帖子</button>
			</div>
		</div>
	</div>
</template>

<script>
	import pubsub from 'pubsub-js'
	import axios from 'axios'
	export default{
		name:'Article',
		data() {
			return{
				Article:''
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/user/myarticle',
				method:'post',
				data:{
					acountname:window.sessionStorage.getItem('acountname')
				}
			}).then((response)=>{
				console.log(response);
				console.log(response.data.article);
				this.Article=response.data.article;	
			}).catch(function(error){
			
			})
		},
		mounted() {
			pubsub.publish('clickIndex',0);
		},
		methods:{
			reEdit(article_id,title){
				console.log('编辑文章 ',article_id,' ',title);
				this.$router.push({
					name:'edituserart',
					query:{
						article_id:article_id
					}
				})
			},
			remove(index,article_id,title){
				console.log('删除文章 ',article_id,' ',title);
				
				this.Article.splice(index,1);
				axios({
					url:'http://127.0.0.1:5000/user/delart',
					method:'post',
					data:{
						article_id:article_id
					}
				}).then((response)=>{
					console.log(response.data);
				}).catch(function(error){
				
				})
			}
		}
	}
</script>

<style scoped>
	#artcle_item{
		display: flex;
		flex-direction: row;
		justify-content: center;
		flex-wrap: wrap;
		
		width: 70%;
		height: 100%;
		overflow-y: auto;
		overflow: scroll;
	}
	.art_data{
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		background-color: rgb(95, 158, 160);
		width: 98%;
		height: 15.125rem;
		border-radius: 5px 5px;
		margin-top: 5px;
	}
	.decde{
		position: relative;
		width: 100%;
		height: 70%;
		overflow: auto;
	}
	.decde div{
		display: flex;
		width: 100%;
		height: auto;
		flex-direction: column;
		justify-content: flex-start;
		align-items: flex-start;
		
		border-top: 0.125rem gray solid;
		text-indent: 2em;
	}
	.score{
		position: absolute;
		
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		bottom: 0;
		width: 100%;
		height: 20%;
		background-color: gray;
	}
	.score span{
		margin: 1.25rem;
	}
	button{
		margin: 0.625rem;
		background: transparent;
		border: none;
		color: red;
		font-size: 20px;
	}
</style>