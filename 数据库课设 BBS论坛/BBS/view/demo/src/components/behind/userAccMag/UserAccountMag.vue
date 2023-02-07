<template>
	<div class="uam">
		<UserInfo></UserInfo>
		<DetailInfo></DetailInfo>
	</div>
</template>

<script>
	import UserInfo from './UserInfo.vue'
	import DetailInfo from './DetailInfo.vue'
	
	export default{
		name:'UserAccountMag',
		data() {
			return{
			}
		},
		components:{
			UserInfo,
			DetailInfo
		}
	}
</script>

<style scoped> 
	.uam{
		height: 100%;
		display: flex;
		flex-direction: row;
		justify-content: flex-start;
		align-items: center;
	}
</style>