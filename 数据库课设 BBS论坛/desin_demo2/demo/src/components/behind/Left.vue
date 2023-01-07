<template>
	<div class="left" @click="Mag($event)">
		<span id="s1" class="item">
			用户账号管理
		</span>
		<span id="s2" class="item">
			帖&nbsp;&nbsp;&nbsp;子&nbsp;&nbsp;管&nbsp;&nbsp;理
		</span>
		<span id="s3" class="item">
			运&nbsp;&nbsp;营&nbsp;&nbsp;数&nbsp;&nbsp;据
		</span>
		<span id="s4" class="item">
			发&nbsp;&nbsp;布&nbsp;&nbsp;公&nbsp;&nbsp;告
		</span>
	</div>
</template>

<script>
	import bHeader from './bHeader.vue'
	import $ from 'jquery'
		
	export default {
		name:'Left',
		data() {
			return{
			}
		},
		methods:{
			Mag(e){
				var s=e.target.id;
				
				if(s=="s1"){
					$("#s1").addClass("sStyleBor");
					$("#s2").removeClass("sStyleBor");
					$("#s3").removeClass("sStyleBor");
					$("#s4").removeClass("sStyleBor");
					this.$router.replace({
						name:'useraccountmag'
					})
				}else if(s=="s2"){
					$("#s2").addClass("sStyleBor");
					$("#s1").removeClass("sStyleBor");
					$("#s3").removeClass("sStyleBor");
					$("#s4").removeClass("sStyleBor");
					this.$router.replace({
						name:'articlemag'
					})
				}else if(s=="s3"){
					$("#s3").addClass("sStyleBor");
					$("#s2").removeClass("sStyleBor");
					$("#s1").removeClass("sStyleBor");
					$("#s4").removeClass("sStyleBor");
					this.$router.replace({
						name:'userregiternum'
					})
				}else{
					$("#s4").addClass("sStyleBor");
					$("#s2").removeClass("sStyleBor");
					$("#s3").removeClass("sStyleBor");
					$("#s1").removeClass("sStyleBor");
					this.$router.replace({
						name:'postnotice'
					})
				}
			}
		}
		
	}

</script>

<style scoped>
	.sStyleBor{
		background-color: orange;
	}
	.left{
		flex: 1;
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		background-color: rgb(44, 49, 60);
		border: 0.7px solid rgb(235, 235, 235);
		border-radius: 5px 5px;
		box-shadow: -2px -2px 0.5em gray;
	}
	.left :first-child {
		margin-top: 20px;
	}
	.item{
		display: flex;
		flex-direction: column;
		justify-content: center;
		
		width: 80%;
		height: 2.5rem;
		
		border: 2px orange solid;
		color: white;
		font-size: 1.25rem;
	}
</style>