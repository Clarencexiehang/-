<template>
	<div class="not">
		<div v-for="(item,index) in notices" class="nitem">
			<div class="con">{{ item.content }}</div>
			<hr>
			<div class="time">{{ item.time }}</div>
			<div class="op">
				<button @click.prevent="toReEditAnnoc(item.aid)">重新编辑</button>
				<button @click.prevent="Remove(item.aid,index)">撤销</button>
			</div>
		</div>
	</div>
</template>

<script>
    import axios from 'axios'
	import pubsub from 'pubsub-js'
	
	export default{
		name:'hasNotices',
		data() {
			return{
				notices:[
				]
			}
		},
		beforeMount() {
			axios({
				url:'http://127.0.0.1:5000/user/getannounc',
				method:'get'
			}).then((response)=>{				
				var ann=response.data.ann;
				console.log('ann :',ann);
				for(var i=0;i<ann.length;i++){
					var an={
						aid:ann[i].Aid,
						content:ann[i].content,
						time:ann[i].posttime
					}
					
					this.notices.push(an);
				}
				
			}).catch((error)=>{
				
			})
		},
		methods:{
			toReEditAnnoc(annoc_id){
				this.$router.push({
					name:'reeditannoc',
					query:{
						aid:annoc_id
					}
				})
			},
			Remove(aid,index){
				console.log('撤销 : ',aid);
				
				this.notices.splice(index,1);
				axios({
					url:'http://127.0.0.1:5000/admin/getanncbyid',
					method:'post',
					data:{
						type:'remove',
						aid:aid
					}
				}).then((response)=>{				
					this.$router.replace({
						name:'hasnotices'
					})
				}).catch((error)=>{
					
				})
			}
		}
	}
</script>

<style scoped>
	.not{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: center;
		
		width: 100%;
		height: 100%;
		overflow: auto;
		background-color: white;
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	.nitem{
		display: flex;
		flex-direction: column;
		justify-content: flex-start;
		align-items: flex-start;
		
		padding: 0.625rem;
		width: 90%;
		height: auto;
		margin-top: 1.625rem;
		border-radius: 0.3125rem 0.3125rem;
		background-color: cadetblue;
	}
	.time{
		color: gray;
	}
	.op{
		display: flex;
		flex-direction: row;
		justify-content: flex-end;
		align-items: center;
		
		width: 100%;
		height: auto;
	}
	.op a{
		color: blue;
		text-decoration: none;
		margin-left: 1.625rem;
	}
	button{
		background-color: rgb(95, 158, 160);
		color: blue;
		font-size: 0.9375rem;
		border: none;
	}
</style>