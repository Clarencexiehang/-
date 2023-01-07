<template>
	<div id="content">
		<div id="item_title">
			<router-link :to="{name:'article'}" :style="styleObj[0].show?styleObj[0].style:null">我的文章 &nbsp;{{ num[0] }}</router-link>
			<router-link :to="{name:'careabout'}" :style="styleObj[1].show?styleObj[1].style:null">我的关注 &nbsp;{{ num[1] }}</router-link>
			<router-link :to="{name:'fans'}" :style="styleObj[2].show?styleObj[2].style:null">我的粉丝 &nbsp;{{ num[2] }}</router-link>
			<router-link :to="{name:'mycollections'}" :style="styleObj[3].show?styleObj[3].style:null">我的收藏 &nbsp;{{ num[3] }}</router-link>
			<router-link :to="{name:'history'}" :style="styleObj[4].show?styleObj[4].style:null">历史记录 &nbsp;{{ num[4] }}</router-link>
		</div>
		<div id="content_detail">
			<router-view></router-view>
		</div>
	</div>
</template>

<script>
	import pubsub from 'pubsub-js'
	import axios from 'axios'
	
	export default{
		name:'ArticleInfo',
		data() {
			return{
				num:[],
				styleObj:[
					{
						show:false,
						style:{
							border:'2px orange solid'
						}
					},
					{
						show:false,
						style:{
							border:'2px orange solid'
						}
					},
					{
						show:false,
						style:{
							border:'2px orange solid'
						}
					},
					{
						show:false,
						style:{
							border:'2px orange solid'
						}
					},
					{
						show:false,
						style:{
							border:'2px orange solid'
						}
					}
				]
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/user/getfournum',
				method:'post',
				data:{
					nickname:window.sessionStorage.getItem('nickname')
				}
			}).then((response)=>{
				this.num=response.data.num;
			}).catch((error)=>{
				
			})
		},
		mounted() {
			pubsub.subscribe('clickIndex',(msg,index)=>{
				for(var i=0;i<=4;i++){
					this.styleObj[i].show=false;
				}
				this.styleObj[index].show=true;
			})
		},
		methods:{
			clickItem(event,index){
				console.log('点击了  ：',index);
			}
		}
	}
</script>

<style scoped>
	#content{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		height: 100%;
		
	}
	#item_title{
		display: flex;
		flex-direction: row;
		justify-content: space-evenly;
		align-items: center;
		
		width: 100%;
		height: 6%;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	#item_title>a{
		flex: 1;
		width: 200px;
		height: 96%;
	}
	a{
		text-decoration: none;
		color: black;
		font-size: 20px;
	}
	#content_detail{
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		margin-top: 0.625rem;
		overflow: auto;
		width: 97%;
		height: 90%;
	}
</style>