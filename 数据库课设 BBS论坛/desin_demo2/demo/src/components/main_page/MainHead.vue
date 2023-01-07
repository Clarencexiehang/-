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
				<input id="key_edit" type="text" placeholder="输入关键词">
				<button id="sbtn" @click="search" :style="styleobj">
					<img id="simg" src="../../assets/icon/search_icon.png" alt="搜索" title="搜索">
				</button>
			</span>
		</span>
		<span id="s3">
			<i class="el-icon-s-opportunity" title="通知" @click="toNotices"></i>
			<i class="el-icon-s-promotion" title="消息"></i>
			<i class="el-icon-s-comment" title="私信" @click="privatesend"></i>
			
			<span id="usename">{{ nickname }}</span>
			<span id="head_span" @click="showHeadItem=true">
				<img id="head_img" v-bind:src="headphoto_path" alt="头像" title="头像">
			</span>
			<ul v-show="showHeadItem" @mouseenter="showHeadItem=true" @mouseleave="showHeadItem=false">
				<li>
					<router-link :to="{name:'article'}" @click="enterPersonpage">进入主页</router-link>
				</li>
				<li>
					<router-link to="/log">退出登录</router-link>
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
				showHeadItem:false
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
					border:'3px solid red'
				}
				timer=setTimeout(()=>{
					this.styleobj=null;
				},100);
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
		
		height: 5%;
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
	}
	#search_span{
		position: relative;
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		width: 100%;
	}
	#key_edit{
		width: 70%;
		height: 1.0625rem;
		border: none;
		border: 0.225rem solid gray;
		font-size: 0.85rem;
	}
	#sbtn{
		width: 2.5rem;
		border: none;
		border: 0.1075rem solid gray;
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
	}
	a{
		text-decoration: none;
		font-size: 15px;
		color: black;
	}
	.el-icon-s-promotion,.el-icon-s-comment,.el-icon-s-opportunity{
		font-size: 25px;
		margin-left: 10%;
	}
	#head_span{
		position: absolute;
		right: 2rem;
		top: 0;
		display: block;
		height: 35px;
		border: 3px solid gray;
		border-radius: 50% 50%;
	}
	#usename{
		position: absolute;
		width: 150px;
		right: 60px;
		overflow-x: auto;
		overflow: auto;
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
</style>