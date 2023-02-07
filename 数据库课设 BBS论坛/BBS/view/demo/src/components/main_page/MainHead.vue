<template>
	<div>
		<span id="s1">
			<img id="logo" src="../../assets/icon/paperBird.png" alt="Logo">
			<router-link :to="{name:'mainfirstpage'}" @click="Flush">首页</router-link>
			<router-link :to="{name:'hotsearchbord'}">热榜</router-link>
			<router-link :to="{name:'care'}">关注</router-link>
		</span>
		<span id="s2">
			<span id="search_span">
				<input id="key_edit" type="text" placeholder="输入关键词" v-model="searchContent">
				<button id="sbtn" @click="search" :style="styleobj" title="搜索关键词">
					<img id="simg" src="../../assets/icon/search_icon.png" alt="搜索" title="搜索">
				</button>
			</span>
		</span>
		<span id="s3">
			<i class="el-icon-s-opportunity" title="通知" @click="toNotices"></i>
			<i class="el-icon-plus" title="发布" @click="postArticle"></i>
			<i class="el-icon-s-comment" title="私信" @click="privatesend"></i>
			
			<span id="usename">{{ nickname }}</span>
			<span id="head_span" @click="showHeadItem=true">
				<img id="head_img" v-bind:src="headphoto_path" alt="头像" title="头像">
			</span>
			<ul v-show="showHeadItem" @mouseenter="showHeadItem=true" @mouseleave="showHeadItem=false">
				<li>
					<router-link :to="{name:'article'}" class="en" @click="enterPersonpage">进入主页</router-link>
				</li>
				<li>
					<router-link to="/log" class="en">退出登录</router-link>
				</li>
			</ul>	
		</span>
	</div>
</template>

<script>
	import axios from 'axios';
    import pubsub from 'pubsub-js'
	export default {
		name:'MainHead',
		data() {
			return{
				nickname:'',
				
				headphoto_path:require('../../assets/navig_img/headphoto.png'),
				styleobj:'',
				showHeadItem:false,
				
				searchContent:''
			}
		},
		beforeMount() {
				this.nickname=window.sessionStorage.getItem('nickname');
		},
		methods:{
			Flush(){
				window.location.reload();
			},
			search(){
				console.log('搜索关键词 ---------');
				this.styleobj={
					border:'3px solid white'
				}
				var timer=setTimeout(()=>{
					this.styleobj=null;
				},100);
				
				if(this.searchContent==''){
					alert('请输入关键词 !');
				}else{
					this.$router.push({
						name:'searchdata',
						query:{
							searchContent:this.searchContent
						}
					})
				}
			},
			toNotices(){
				this.$router.push({
					name:'notices'
				})
			},
			privatesend(){
				this.$router.push({
					name:'msglist'
				})
			},
			enterPersonpage(){
				axios({
					
				})
			},
			postArticle(){
				this.$router.push({
					name:'postarticle'
				})
			}
		}
	}
</script>

<style scoped>
	div{
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: space-between;
		align-items: center;
		
		background-color: rgb(252, 85, 49);
		height: 7%;
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	#s1{
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: space-evenly;
		align-items: center;
		
		width: 40%;
	}
	#logo{
		position: absolute;
		top: 0;
		width: 20%;
		left: 0;
		z-index: 5;
	}
	#s2{
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		width: 40%;
		height: 60%;
	}
	#search_span{
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		width: 100%;
		height: 100%;
	}
	#key_edit{
		flex: 4;
		height: 100%;
		border: none;
		font-size: 0.98rem;
		border-radius: 0.3125rem 0.3125rem;
		border: 0.125rem purple solid;
		padding-left: 2%;
	}
	#sbtn{
		flex: 1;
		height: 100%;
		border: none;
		border-radius: 0.3125rem 0.3125rem;
		border: 0.125rem purple solid;
		background-color: slateblue;
	}
	#simg{
		height: 1.1625rem;
	}
	#s3{
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 40%;
		height: 100%;
	}
	a{
		text-decoration: none;
		font-size: 20px;
		color: white;
	}
	.el-icon-plus,.el-icon-s-comment,.el-icon-s-opportunity{
		font-size: 25px;
		margin-left: 10%;
	}
	#head_span{
		position: absolute;
		right: 2rem;
		top: 0;
		display: block;
		height: 90%;
		border: 3px solid gray;
		border-radius: 50% 50%;
	}
	#usename{
		position: absolute;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		width: 150px;
		height: 100%;
		right: 60px;
		overflow-x: auto;
		overflow: auto;
		
		color: white;
		font-size: 20px;
	}
	#head_img{
		height: 100%;
	}
	ul{
		position: absolute;
		right: 1.0625rem;
		top: 2.875rem;
		z-index: 4;
	}
	li{
		list-style: none;
		margin: 0;
		border: 2px solid gray;
		color: black;
		background-color: rgb(240, 255, 255);
	}
	.en{
		color: black;
	}
</style>