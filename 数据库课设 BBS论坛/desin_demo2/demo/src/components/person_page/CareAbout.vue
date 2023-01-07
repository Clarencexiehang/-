<template>
	<div id="care_item">
		<div class="care_data" v-for="(use,index) in careUser" :key="index">
			<div class="use_info" @click="enterUser($event,use)">
				<span class="head">
					<img src="../../assets/icon/head.png" class="head_img" alt="用户头像">
				</span>
				<span class="nickname">{{ use }}</span>
				<button class="cal_care" @click="cancel_Care(index,use)">取消关注</button>
			</div>
		</div>
	</div>
</template>

<script>
	import pubsub from 'pubsub-js'
	import axios from 'axios'
	
	export default{
		name:'CareAbout',
		data() {
			return {
				careUser:''
			}
		},
		methods:{
			enterUser:function($event,use){
				this.$router.replace({
					name:'articledetail',
					params:{
						cnickname:use
					}
				})
			}
		},
		mounted() {
			axios({
				url:'http://127.0.0.1:5000/user/mycare',
				method:'post',
				data:{
					acountname:window.sessionStorage.getItem('acountname')
				}
			}).then((response)=>{
				this.careUser=response.data.careUser;
				
			}).catch(function(error){
			
			})
			pubsub.publish('clickIndex',1);
		},
		methods: {
			cancel_Care(index,nickname){
				console.log('取消关注  : ',nickname);
				this.careUser.splice(index,1);
				axios({
					url:'http://127.0.0.1:5000/user/cancelcare',
					method:'post',
					data:{
						accountname:window.sessionStorage.getItem('acountname'),
						nickname:nickname
					}
				}).then((response)=>{
					
				}).catch(function(error){
				
				})
			}
		}

	}
</script>

<style scoped>
	#care_item{
		width: 70%;
		height: 100%;
		overflow-y: auto;
		overflow: scroll;
	}
	.care_data{
		position: relative;
		width: 98%;
		height: 3.125rem;
		padding: 0.625rem;
		margin-top: 0.625rem;
		background-color: rgb(95, 158, 160);
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
	}
	
	.cal_care{
		position: absolute;
		width: 6.25rem;
		height: 2.5rem;
		right: 0.625rem;
		color: red;
		font-size: 1.25rem;
	}
	.use_info{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
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
</style>