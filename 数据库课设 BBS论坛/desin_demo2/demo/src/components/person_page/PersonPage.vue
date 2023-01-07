<template>
	<div id="content">
		<div id="title">
			<h1>个 &nbsp;&nbsp;人&nbsp;&nbsp;中&nbsp;&nbsp;心</h1>
		</div>
		<div id="per_content">
			<span id="info">
				<span id="head">
					<img id="headimg" :src="headpath" alt="">
				</span>
				<span class="item">
					<label class="label">昵称:</label> 
					<span class="cont">
						{{nickname}}
					</span>
				</span>
				<span class="item">
					<label class="label">账号:</label>
					<span class="cont">
						{{acountname}}
					</span>
				</span>
				<span class="item">
					<label class="label">文章:</label>
					<span class="cont">
						{{articleNum}}
					</span>
				</span>
				<span class="item">
					<label class="label">关注:</label>
					<span class="cont">
						{{careNum}}
					</span>
				</span>
				<span class="item">
					<label class="label">粉丝:</label>
					<span class="cont">
						{{careNum}}
					</span>
				</span>
				<button>
					<router-link :to="{name:'modify'}">修 &nbsp;改 &nbsp;信 &nbsp;息</router-link>
				</button>
			</span>
			<span id="per_op">
				<router-view></router-view>
			</span>
		</div>
	</div>
</template>

<script>
	import pubsub from 'pubsub-js'
    import {mapState} from 'vuex'
	import axios from 'axios'
	
	export default {
		name:'PersonPage',
		data() {
			return{
				headpath:require('../../assets/icon/head.png'),
				nickname:window.sessionStorage.getItem('nickname'),
				acountname:window.sessionStorage.getItem('acountname'),
				articleNum:0,
				careNum:0
			}
		},
		computed:{
			/* ...mapState("useInfo",{headpath:"headpath",nickname:"nickname",acount:"acount",articleNum:"articleNum"}), */
		},
		beforeMount() {
			var nickname=window.sessionStorage.getItem('nickname');
			if(nickname!=null){
				axios({
					url:'http://127.0.0.1:5000/user/userinfo',
					method:'post',
					data:{
						type:'getArticle',
						nickname:window.sessionStorage.getItem('nickname')
					}
				}).then((response)=>{
					console.log(response);
					console.log('--------- Personpage  info --------- ');
					console.log(response.data.userinfo.nickname);
					console.log(response.data.userinfo.acountname);
					console.log(response.data.userinfo.articlenum);
					
					this.nickname=response.data.userinfo.nickname;
					this.acountname=response.data.userinfo.acountname;
					this.articleNum=response.data.userinfo.articlenum;
					this.careNum=response.data.userinfo.carenum;
					
				}).catch(function(error){
					
				})
			}else{
				console.log('请先登录 ！');
				this.$router.replace({
					path:'/log'
				})
			}
		}
	}
</script>

<style scoped>
	#content{
		position: relative;
		height: 88%;
		margin-top: 0.3125rem;
	}
	#title{
		display: flex;
		flex-direction: row;
		justify-content: center;
		align-items: center;
		
		height: 10%;
		background-color: rgb(245, 222, 179);
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	#title h1{
		color: orange;
	}
	#per_content{
		display: flex;
		flex-direction: row;
		justify-content: center;
		height: 90%;
		margin-top: 0.3125rem;
	}
	#info{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		flex:1;
		
		height: 100%;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	#head{
		display: block;
		width: 150px;
		height: 150px;
		border: 9px solid gray;
		border-radius: 50% 50%;
	}
	#headimg{
		width: 100%;
	}
	.item{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		width: 70%;
		height: 10%;
		float: left;
	}
	.cont{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
		
		float: right;
		width: 8.3375rem;
		height: 50%;
		overflow: auto;
	}
	.label{
		font-weight:60 ;
	}
	button{
		width: 60%;
		height: 2.575rem;
		border-radius: 0.3875rem 0.3875rem;
		margin-top: 1.65rem;
		background-color: dodgerblue;
	}
	button a{
		text-decoration: none;
		font-size: 20px;
		color: black;
	}
	#per_op{
		position: relative;
		display: flex;
		flex-direction: row;
		/* border: 3px solid red; */
		flex:4;

		overflow: auto;
		margin-top: 0.1875rem;
		margin-left: 0.3125rem;
	}

</style>