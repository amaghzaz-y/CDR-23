import { writable } from "svelte/store";

export const HostIP = writable("192.168.4.1");
export let baseURL = ""
HostIP.subscribe(value => {
	baseURL = `http://${value}`
})
