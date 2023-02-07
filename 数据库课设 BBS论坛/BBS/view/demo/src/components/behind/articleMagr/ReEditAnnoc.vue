<template>
	<div class="rean">
		<textarea v-model="ancontent"></textarea>
		<button id="cancel" @click="cancelModifyAnnc">取&nbsp;&nbsp;消&nbsp;&nbsp;更&nbsp;&nbsp;改</button>
		<button id="mos" @click="toModifyAnnc">确&nbsp;&nbsp;认&nbsp;&nbsp;更&nbsp;&nbsp;改</button>
	</div>
</template>

<script>
	import pubsub from 'pubsub-js'
	import axios from 'axios'
	
	export default{
		name:'ReEditAnnoc',
		data() {
			return{
				Aid:'',
				ancontent:''
			}
		},
		beforeMount() {
			this.Aid=this.$route.query.aid
			
			axios({
				url:'http://127.0.0.1:5000/admin/getanncbyid',
				method:'post',
				data:{
					type:'get',
					aid:this.Aid
				}
			}).then((response)=>{				
				this.ancontent=response.data.content;
			}).catch((error)=>{
				
			})
		},
		methods:{
			toModifyAnnc(){
				axios({
					url:'http://127.0.0.1:5000/admin/getanncbyid',
					method:'post',
					data:{
						type:'modify',
						aid:this.Aid,
						content:this.ancontent
					}
				}).then((response)=>{				
					var status=response.data.status;
					if(status=='ok'){
						alert('公告修改成功 ！');
						this.$router.replace({
							name:'hasnotices'
						})
					}else{
						alert('公告修改异常 ！');
					}
				}).catch((error)=>{
					
				})
			},
			cancelModifyAnnc(){
				this.$router.back();
			}
		}
	}
</script>

<style scoped>
	.rean{
		display: flex;
		flex-direction: column;
		justify-content: space-between;
		align-items: center;
		
		width: 100%;
		height: 100%;
		overflow: auto;
	}
	
	textarea{
		width: 70%;
		height: 60%;
	}
	#cancel{
		width: 25rem;
		height: 2.5rem;
		background-color: green;
		color: white;
		font-size: 1.25rem;
	}
	#mos{
		width: 25rem;
		height: 2.5rem;
		margin-bottom: 2.25rem;
		background-color: red;
		color: white;
		font-size: 1.25rem;
	}
</style>