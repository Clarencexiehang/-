<template>
	<div id="collect_item">
		<div class="collect_data" v-for="(item,index) in art" :key="index">
			<div class="authInfo" title="点击进入文章详情" @click="ArticleDetail(item.nickname,item.article_id)">
				<span class="head">
					<img v-bind:src="item.headpath" class="head_img" alt="用户头像">
				</span>
				<span class="nickname">{{ item.nickname }}</span>
			</div>
			<div class="tyty" title="点击进入文章详情" @click="ArticleDetail(item.nickname,item.article_id)">
				<h3> {{ item.title }}</h3>
			</div>
			<div class="colleTime">
				<i class="el-icon-s-opportunity" title="点赞">{{ item.agreenum }}</i>
				<span class="tty">收藏时间 : 2022-12-12</span>
				<button class="ccll" @click="cancelCollect(index,item.article_id)">取消收藏</button>
			</div>
		</div>
	</div>
</template>

<script>
	import axios from 'axios';
	import pubsub from 'pubsub-js'
	export default{
		name:'MyCollections',
		mounted() {
			pubsub.publish('clickIndex',3);
		},
		data() {
			return{
				art:[]
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/user/getcollecart',
				method:'post',
				data:{
					acountname:window.sessionStorage.getItem('acountname')
				}
			}).then((response)=>{
				console.log(response.data);
				var cArtList=response.data.cArtList;
				
				for(var i=0;i<cArtList.length;i++){
					var art={
						nickname:cArtList[i].nickname,
						accountname:cArtList[i].author_acountname,
						headpath:require('../../assets/icon/head.png'),
						article_id: cArtList[i].article_id,
						title: cArtList[i].title,
						content: cArtList[i].content,
						posttime: cArtList[i].posttime,
						agreenum: cArtList[i].agreenum
					}
					
					this.art.push(art);
				}
			}).catch((error)=>{
				
			})
		},
		methods:{
			ArticleDetail(nickname,article_id){
				
				/* 跳转到详情 */
				this.$router.push({
					name:'articledetail',
					params:{
						cnickname:nickname,
						article_id:article_id
					}
				})
			},
			cancelCollect(index,article_id){
				console.log('取消收藏  : ',index,' ',article_id);
				this.art.splice(index,1);
				axios({
					url:'http://127.0.0.1:5000/user/cancelcollec',
					method:'post',
					data:{
						accountname:window.sessionStorage.getItem('acountname'),
						article_id:article_id
					}
				}).then((response)=>{
					
				}).catch((error)=>{
					
				})
			}
		}
	}
</script>

<style scoped>
	#collect_item{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 70%;
		height: 100%;
		overflow-y: auto;
		overflow: scroll;
	}
	.collect_data{
		display: flex;
		flex-direction: column;
		justify-content: space-between;
		
		padding: 0.625rem;
		background-color: rgb(95, 158, 160);
		width: 90%;
		height: 10.125rem;
		margin-top: 0.625rem;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
	}
	.authInfo{
		border-bottom: gray 0.125rem solid;
	}
	.head{
		float: left;
		width: 2.5rem;
		height: 2.5rem;
		border-radius: 50% 50%;
	}
	.nickname{
		float: left;
		margin-left: 1.25rem;
		height: 100%;
		
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
	}
	.head_img{
		width: 100%;
	}
	
	.colleTime{
		display: flex;
		height: auto;
		
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		padding: 0.325rem;
		background-color: gray;
		width: 100%;
		height: 30%;
	}
	.ccll{
		margin-left: 0.625rem;
		width: 6.25rem;
		height: 1.875rem;
		color: red;
		font-size: 1.25rem;
		background: transparent;
		border: none;
	}
	.tty{
		color: red;
		margin-left: 0.625rem;
		margin-right: 0.625rem;
	}
	.tyty{
		width: 100%;
	}
</style>