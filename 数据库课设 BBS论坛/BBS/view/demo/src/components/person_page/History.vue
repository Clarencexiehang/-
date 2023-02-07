<template>
	<div id="hist_item">
		<div class="hist_data" v-for="(item,index) in history" :key="index">
			<div class="authInfo" title="点击进入文章详情" @click="enterArticleDetail(item.nickname,item.article_id)">
				<span class="head">
					<img v-bind:src="require('../../assets/icon/head.png')" class="head_img" alt="用户头像">
				</span>
				<span class="nickname">{{ item.nickname }}</span>
			</div>
			<div class="tdtd" title="点击进入文章详情" @click="enterArticleDetail(item.nickname,item.article_id)">
				<h3> {{ item.title }}</h3>
			</div>
			<div class="colleTime">
				<i class="el-icon-s-opportunity" title="点赞">{{ item.agreenum }}</i>
				<span class="tytt">浏览于 : {{ item.readtime }}</span>
				<button class="ccll" @click="clearHist(index,item.article_id)">清除历史</button>
			</div>
		</div>
	</div>
</template>

<script>
	import pubsub from 'pubsub-js'
	import axios from 'axios'
	
	export default{
		name:'History',
		mounted() {
			pubsub.publish('clickIndex',4);
		},
		data() {
			return{
				history:[
				]
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/user/gethistory',
				method:'post',
				data:{
					accountname:window.sessionStorage.getItem('acountname'),
				}
			}).then((response)=>{
				console.log('历史数据 ----------',response.data);
				this.history=response.data.history;
			}).catch((error)=>{
				
			})
		},
		methods:{
			enterArticleDetail(nickname,article_id){
			    this.$router.replace({
			    	name:'articledetail',
					params:{
						cnickname:nickname,
						article_id:article_id
					}
			    })
			},
			clearHist(index,article_id){
				this.history.splice(index,1);
				axios({
					url:'http://127.0.0.1:5000/user/clrhistory',
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
	#hist_item{
		width: 70%;
		height: 100%;
		overflow-y: auto;
		overflow: scroll;
	}
	.hist_data{
		width: 98%;
		height: 10.125rem;
		margin-top: 0.625rem;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		background-color: rgb(95, 158, 160);
		padding: 0.625rem;
	}
	.authInfo{
		height: 50px;
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
		
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		background-color: gray;
		height: 50px;
		padding: 3px;
	}
	.ccll{
		margin-left: 0.625rem;
		width: 6.25rem;
		height: 1.875rem;
		color: red;
		font-size: 1.25rem;
		background: transparent;
		border:none;
	}
	.tytt{
		color: red;
		margin-left: 0.625rem;
		margin-right: 0.625rem;
	}
	.tdtd{
		width: 100%;
	}
</style>