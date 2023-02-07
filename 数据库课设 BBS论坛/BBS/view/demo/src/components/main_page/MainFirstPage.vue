<template>
	<div id="first">
		<div v-for="(value,index) in art" class="item" @click.passive="toArticleDetail($event,value.nickname,value.article_id)">
			<!-- 用户信息 -->
			<div class="use_info">
				<span class="head">
					<img v-bind:src="value.headpath" class="head_img" alt="用户头像">
				</span>
				<span class="nickname">{{ value.nickname }}</span>
			</div>
			<!-- 帖子标题 -->
			<div class="title">
				<h4>{{ value.title }}</h4>
				<i v-if="!value.show" @click.stop="value.show=!value.show" class="el-icon-arrow-right"></i>
				<i v-else @click.stop="value.show=!value.show" class="el-icon-arrow-down"></i>
			</div>
			<!-- 帖子内容 -->
			<div  v-show="value.show" class="content" @click="enterArticle($event,value.nickname,value.article_id)">
				<!-- 内容摘要 -->
				<span class="summery">
					<mark>摘要 :</mark>
					{{ value.content }}
				</span>
			</div>
			<div class="agree">
				<i class="el-icon-s-opportunity" title="点赞" @click.stop="addAgreeNum(index,value.article_id)">{{ value.agreenum }}</i>
				<i v-if="!value.hasbeCollected" class="el-icon-star-off" title="收藏" @click.stop="noCollect(index,value.article_id)">{{ value.collnum }}</i>
				<i v-else class="el-icon-star-on" title="收藏" @click.stop="hasCollect">{{ value.collnum }}</i>
				<i class="el-icon-edit" title="评论" @click.stop="toArticleDetail($event,value.nickname,value.article_id)"></i>
				<i class="el-icon-delete" title="从会话列表删除" @click.stop="deletArt($event,index,value.nickname)"></i>
			</div>
		</div>
		
		
		
	</div>
</template>

<script>
	import axios from 'axios';
	import pubsub from 'pubsub-js'
	export default{
		name:'MainFirstPage',
		data() {
			return{
				artHoverStyle:'',
				activeNames: ['1'],
				art:[
				]
			}
		},
		beforeMount() {
			console.log('请求---------------------');
		    	axios({
					url:'http://127.0.0.1:5000/view/index',
					method:'post',
					data:{
						acountname:window.sessionStorage.getItem('acountname')
					}
				}).then((response)=>{
					
					var articleList=response.data.articleList;
					console.log('------ articleList --------',articleList);
					console.log('------ articleList length--------',articleList.length);
					
				
					for(var i=0;i<articleList.length;i++){
					
						console.log('    i : ',i);
						console.log('    a : ',articleList[i]);
						var newarticle={
							index:i,
							article_id:articleList[i].article.article_id,
							nickname:articleList[i].nickname,
							headpath:require('../../assets/icon/head.png'),
							title:articleList[i].article.title,
							hasImg:true,
							agreenum:articleList[i].article.agreenum,
							content:articleList[i].article.content,
							collnum:articleList[i].article.collnum,
							hasbeCollected:articleList[i].article.hasbeCollected,
							show:false
						}
						
						console.log('------ newarticle  ---' ,newarticle);
						this.art.push(newarticle);
						
						
						console.log('------ bbbbbbbbb  ---');
					
					}
					
				}).catch((error)=>{
					
				})
		},
		methods: {
			addAgreeNum(index,article_id){
				console.log('点赞 +1  ------- ',index,'  :  ',article_id);
				var n=this.art[index].agreenum;
				
				this.art[index].agreenum=n+1;
				
				axios({
					url:'http://127.0.0.1:5000/article/addartagreenum',
					method:'post',
					data:{
						article_id:article_id
					}
				}).then((response)=>{
					
				}).catch((error)=>{
					
				})
				
			},
			noCollect(index,article_id){
				console.log(window.sessionStorage.getItem('acountname'),' 收藏 ',index,' ',article_id);
				
				this.art[index].collnum=this.art[index].collnum+1;
				this.art[index].hasbeCollected=!this.art[index].hasbeCollected;
				
				axios({
					url:'http://127.0.0.1:5000/user/addcollect',
					method:'post',
					data:{
						acountname:window.sessionStorage.getItem('acountname'),
						article_id:article_id
					}
				}).then((response)=>{
					console.log('收藏结果',response.data);
					if(response.data.status=='no'){
						alert('该文章已被收藏过 !');
					}
				}).catch((error)=>{
					
				})
				
			},
			hasCollect(){
				alert('该文章已被收藏过 !');
			},
		    handleChange(val) {
		        console.log(val);
		    },
			enterArticle(event,nickname,article_id){
				this.$router.replace({
					name:'articledetail',
					params:{
						cnickname:nickname,
						article_id:article_id
					}
				})
			},
			toArticleDetail(event,nickname,article_id){
			    this.$router.push({
			    	name:'articledetail',
					params:{
						cnickname:nickname,
						article_id:article_id
					}
			    })
			},
			deletArt($event,index,nickname){
				this.art.splice(index,1);
			}
		}
	}
</script>

<style scoped>
	#first{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 60%;
		height: 98%;
		border: 0.7px solid gray;
		box-shadow: -2px -2px 0.5em gray;
		margin-top: 5px;
		
		overflow: auto;
	}
	.item{
		background-color: cadetblue;
		width: 95%;
		padding:10px;
		margin-top: 1.625rem;
		border: 1.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
	}
	.use_info{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
	
		height: 2.5rem;
	}
	.head{
		float: left;
		width: 2.5rem;
		height: 2.5rem;
		border-radius: 50% 50%;
	}
	.nickname{
		float: left;
	}
	.head_img{
		width: 100%;
	}
	mark{
		background: none;
		font-size: 20px;
	}
	.title{
		position: relative;
		width: 100%;
		height: 40px;
	}
	.title i{
		position: absolute;
		top: 0.6875rem;
		right: 1.0625rem;
	}
	.content{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: flex-start;
		
		width: 100%;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
	}
	.img{
		display: block;
		float: left;
		flex: 1;
		height: 100px;
		
		border: 0.7px solid red;
		border-radius: 5px 5px;
	}
	.summery{
		float: left;
		display: block;
		flex: 4;
		
		height: 100px;
		border-radius: 5px 5px;

	}
	.agree{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		height: 40px;
		border-top: 0.125rem gray solid;
	}
	.agree i{
		font-size: 20px;
		margin-left: 1.25rem;
	}
	
</style>