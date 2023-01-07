<template>
	<div class="artMg">
		<span class="artLeftItem" @click="spanClick($event)">
			<span id="a1">用户帖子</span>
			<span id="a2">已发公告</span>
		</span>
		<span class="artDetail">
			<router-view></router-view>
		</span>
	</div>
</template>

<script>
	import $ from 'jquery'
	
	export default{
		name:'ArticleMag',
		data() {
			return{}
		},
		methods:{
			spanClick(e){
				var s=e.target.id;
				console.log(s);
				if(s=="a1"){
					$("#a1").addClass("sStyleBor");
					$("#a2").removeClass("sStyleBor");
					this.$router.push({
						name:'userart'
					})
				}else if(s=="a2"){
					$("#a2").addClass("sStyleBor");
					$("#a1").removeClass("sStyleBor");
					this.$router.push({
						name:'hasnotices'
					})
				}
			}
		}
	}
</script>

<style scoped>
	.artMg{
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		
		width: 100%;
		height: 100%;
		overflow: auto;
	}
	.artLeftItem{
		flex: 1;
		
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
	}
	.sStyleBor{
		background-color: orange;
	}
	.artLeftItem span{
		display: flex;
		flex-direction: column;
		justify-content: center;
		align-items: center;
		
		color: royalblue;
		font-size: 1.4995rem;
		width: 100%;
		height: 2.125rem;
		border: 2px orange solid;
	}
	.artDetail{
		flex: 5;
	}
</style>